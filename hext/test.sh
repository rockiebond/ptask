#!/bin/bash
hhvm -d hhvm.dynamic_extensions[]=ptask.so -d hhvm.enable_zend_compat=1 test.php
