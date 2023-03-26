package collections;

import java.util.*;
import java.lang.reflect.*;
import java.util.Map.Entry;

// refer: https://ivoanjo.me/blog/2018/07/21/writing-to-a-java-treemap-concurrently-can-lead-to-an-infinite-loop-during-reads/
@SuppressWarnings("unchecked")
public class ConcurrentTreeMapLoopReproducer {
  public static void main(String ... args) throws Exception {
    System.out.println("Running on Java " + System.getProperty("java.version"));
    int insertUpTo = 20;
    if (args.length > 0) {
      insertUpTo = Integer.parseInt(args[0]);
    }
    System.out.println("Using insertUpTo=" + insertUpTo);

    new ConcurrentTreeMapLoopReproducer(insertUpTo).call();
  }

  TreeMap<Integer,Integer> brokenMap = null;
  int insertUpTo;

  ConcurrentTreeMapLoopReproducer(int insertUpTo) {
    this.insertUpTo = insertUpTo;
  }

  static class LoopStep {
    Entry<Integer,Integer> entry;
    String direction;
    LoopStep next;

    LoopStep(Entry<Integer,Integer> entry) { this(entry, null, null); }
    LoopStep(Entry<Integer,Integer> entry, String direction, LoopStep next) {
      this.entry = entry;
      this.direction = direction;
      this.next = next;
    }

    public String toString() {
      if (next != null) {
        return "" + entry.getKey() + " --" + direction + "--> " + next;
      } else {
        return entry.getKey().toString();
      }
    }
  }

  public void call() throws Exception {
    LoopStep loopPath = null;
    System.out.print("Attempting to trigger looping TreeMap");
    for (int attempts = 1; loopPath == null; attempts++) {
      System.out.print(".");
      System.out.flush();

      brokenMap = tryToTriggerLoopingTreeMap();
      loopPath = findLoop(brokenMap);
    }

    System.out.println("\nWas able to reproduce loop in map: " + loopPath);

    // Uncomment this to see the loop in action: This will never finish
    //brokenMap.values().toArray();
  }

  static TreeMap<Integer,Integer> tryToTriggerLoopingTreeMap() throws Exception {
    TreeMap<Integer,Integer> map = new TreeMap<>();

    Thread t1 = new Thread(() -> {
      for (int i = 0; i < 90; i ++) {
        try {
          for (int j = 0; j < 10; j++) {
            map.put(j, i);
          }
        } catch (Exception e) {
        }
      }
    });
    Thread t2 = new Thread(() -> {
      for (int i = 90; i < 100; i ++) {
        try {
          for (int j = 0; j < 10; j++) {
            map.put(j, i);
          }
        } catch (Exception e) {
        }
      }
    });
    t1.start();
    t2.start();
    t1.join();
    t2.join();

    return map;
  }

  static LoopStep findLoop(TreeMap<Integer,Integer> map) throws Exception {
    Field rootField = TreeMap.class.getDeclaredField("root");
    rootField.setAccessible(true);

    Entry<Integer,Integer> rootEntry = (Entry<Integer,Integer>) rootField.get(map);

    return findLoopRecursive(new ArrayList<>(), rootEntry);
  }

  static LoopStep findLoopRecursive(List<Entry<Integer,Integer>> currentPath, Entry<Integer,Integer> entry) throws Exception {
    if (entry == null) {
      return null;
    }

    if (currentPath.contains(entry)) {
      currentPath.add(entry);
      return new LoopStep(entry);
    }

    currentPath.add(entry);

    LoopStep result = null;

    result = findLoopRecursive(currentPath, get("left", entry));
    if (result != null) {
      return new LoopStep(entry, "left", result);
    }
    result = findLoopRecursive(currentPath, get("right", entry));
    if (result != null) {
      return new LoopStep(entry, "right", result);
    }

    currentPath.remove(entry);

    return null;
  }

  static Entry<Integer,Integer> get(String direction, Entry<Integer,Integer> parent) throws Exception {
    Field field = parent.getClass().getDeclaredField(direction);
    field.setAccessible(true);
    return (Entry<Integer,Integer>) field.get(parent);
  }
}