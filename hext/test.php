<?php
var_dump(extension_loaded("ptask"));
var_dump(function_exists("ptask_create"));
function handler($arg)
{
	for ($i = 0; $i < 1000; $i++) {
		echo $arg, ": ", $i, "\n";
		ptask_yield();
	}
}


ptask_create("handler", "handler1");
ptask_create("handler", "handler2");

ptask_run();

