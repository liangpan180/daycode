/*
 * test for load python in C program
 */

#include <Python.h>

int main(int argc, char **argv)
{
	int ret = 0;
	PyObject *pName = NULL;
	PyObject *pModule = NULL;
	PyObject *pFunc = NULL;

	Py_Initialize();

	PyRun_SimpleString("import math");
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	PyRun_SimpleString("sys.path.append('./test/')");

	pName = PyString_FromString("helloWorld");
	if (!pName) {
		printf("PyString_FromString failed !\n");
		ret = -1;
		goto out;
	}

	pModule = PyImport_Import(pName);
	if (!pModule) {
		printf("PyImport_Import failed !\n");
		ret = -1;
		goto out;
	}

	pFunc = PyObject_GetAttrString(pModule, "hello");
	if (!pFunc) {
		printf("PyObject_GetAttrString failed !\n");
		ret = -1;
		goto out;
	}

	PyEval_CallObject(pFunc, NULL);

	Py_Finalize();

out:
	return ret;
}
