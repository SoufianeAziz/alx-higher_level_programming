#include <Python.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);

/**
 * print_python_list - Prints information about Python lists
 * @p: Pointer to a Python object
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t i, size;
	PyObject *element;

	size = PyList_Size(p);

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);

	for (i = 0; i < size; i++)
	{
		element = PyList_GetItem(p, i);
		printf("Element %ld: %s\n", i, Py_TYPE(element)->tp_name);
		if (PyBytes_Check(element))
			print_python_bytes(element);
	}
}

/**
 * print_python_bytes - Prints information about Python bytes objects
 * @p: Pointer to a Python object
 */
void print_python_bytes(PyObject *p)
{
	Py_ssize_t i, size;
	char *str;

	printf("[.] bytes object info\n");
	size = PyBytes_Size(p);
	printf("  size: %ld\n", size);
	str = PyBytes_AsString(p);

	if (!str)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	printf("  trying string: %s\n", str);

	if (size > 10)
		size = 10;

	printf("  first %ld bytes: ", size);
	for (i = 0; i < size; i++)
	{
		printf("%02hhx", str[i]);
		if (i < size - 1)
			printf(" ");
		else
			printf("\n");
	}
}

