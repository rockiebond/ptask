set(HPHP_HOME "/home/rockie/opensource/hhvm/")
include_directories(
    ./
    /home/rockie/opensource/hhvm/hphp/runtime/ext_zend_compat/php-src
    /home/rockie/opensource/hhvm/hphp/runtime/ext_zend_compat/php-src/Zend/
    /home/rockie/opensource/hhvm/hphp/runtime/ext_zend_compat/php-src/TSRM/
    /home/rockie/opensource/hhvm/hphp/runtime/ext_zend_compat/php-src/main/
)
HHVM_EXTENSION(ptask ptask.cpp)
HHVM_SYSTEMLIB(ptask ext_ptask.php)
target_link_libraries(ptask libtask.a)
