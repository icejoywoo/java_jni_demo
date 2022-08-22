#!/bin/bash

set -xeu

CURRENT_DIR=$(cd `dirname $0`; pwd)

BUILD_DIR=release-build

# build jni library
(
  cd ${CURRENT_DIR}
  [ -d ${BUILD_DIR} ] && rm -rfv ${BUILD_DIR}
  mkdir ${BUILD_DIR}
  cd ${BUILD_DIR}
  cmake .. -G Ninja
  cmake --build .
)

# build jar
(
  mvn clean package
)

# run jar
(
  echo "running demo.HelloJni:"
  ${JAVA_HOME}/bin/java -cp ${CURRENT_DIR}/target/*.jar demo.HelloJni

  echo "running jni.JniDemo:"
  ${JAVA_HOME}/bin/java -cp ${CURRENT_DIR}/target/*.jar -Djava.library.path=${CURRENT_DIR}/${BUILD_DIR} jni.JniDemo
)
