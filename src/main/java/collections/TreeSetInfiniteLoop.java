package collections;

import java.util.Collections;
import java.util.Set;
import java.util.TreeSet;

public class TreeSetInfiniteLoop {

  public static void main(String[] args) throws InterruptedException {

    for (int attempt = 0; true; attempt++) {
//      Set<Integer> set = Collections.synchronizedSet(new TreeSet<>());
      Set<Integer> set = new TreeSet<>();

      Thread t1 = new Thread(() -> {
        for (int i = 0; i < 90; i++) {
          for (int j = 0; j < 10; j++) {
            try {
              set.add(j);
            } catch (Exception e) {
              // ignore
            }
          }
        }
      });

      Thread t2 = new Thread(() -> {
        for (int i = 90; i < 100; i++) {
          for (int j = 0; j < 10; j++) {
            try {
              set.add(j);
            } catch (Exception e) {
              // ignore
            }
          }
        }
      });
      t1.start();
      t2.start();
      t1.join();
      t2.join();

      Thread t3 = new Thread(() -> {
        int counter = 0;
        for (Integer value : set) {
          counter++;
          if (counter > 100) {
            System.out.println("infinite loop found.");
            System.exit(-1);
          }
        }
      });
      t3.start();
      t3.join();

      if (attempt % 100 == 0) {
        System.out.println(String.format("attempting %d ...", attempt));
      }
    }
  }
}
