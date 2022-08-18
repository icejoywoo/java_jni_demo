#!/bin/bash

set -xeu

CURRENT_DIR=$(cd `dirname $0`; pwd)

cd ${CURRENT_DIR}

mvn compile

cd ${CURRENT_DIR}/target/classes

${JAVA_HOME}/bin/javah -d ${CURRENT_DIR}/jni_lib/jni jni.JniWrapper
