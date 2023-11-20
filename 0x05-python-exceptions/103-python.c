#include <Python.h>

void print_python_list(PyObject *p) {
    Py_ssize_t size, i;
    PyObject *item;

    if (!PyList_Check(p)) {
        fprintf(stderr, "[*] Python list info\n  [ERROR] Invalid List Object\n");
        return;
    }

    size = PyList_Size(p);
    fprintf(stdout, "[*] Python list info\n[*] Size of the Python List = %ld\n[*] Allocated = %ld\n", size, ((PyListObject *)p)->allocated);

    for (i = 0; i < size; i++) {
        item = PyList_GetItem(p, i);
        fprintf(stdout, "Element %ld: %s\n", i, Py_TYPE(item)->tp_name);
        if (PyBytes_Check(item)) {
            print_python_bytes(item);
        } else if (PyFloat_Check(item)) {
            print_python_float(item);
        }
    }
}

void print_python_bytes(PyObject *p) {
    Py_ssize_t size, i;
    char *str;

    if (!PyBytes_Check(p)) {
        fprintf(stderr, "[.] bytes object info\n  [ERROR] Invalid Bytes Object\n");
        return;
    }

    size = PyBytes_Size(p);
    str = PyBytes_AsString(p);

    fprintf(stdout, "[.] bytes object info\n  size: %ld\n  trying string: %s\n  first %ld bytes: ", size, str, (size > 10) ? 10 : size);
    for (i = 0; i < size && i < 10; i++) {
        fprintf(stdout, "%02x", (unsigned char)str[i]);
        if (i < 9) {
            fprintf(stdout, " ");
        }
    }
    fprintf(stdout, "\n");
}

void print_python_float(PyObject *p) {
    if (!PyFloat_Check(p)) {
        fprintf(stderr, "[.] float object info\n  [ERROR] Invalid Float Object\n");
        return;
    }

    fprintf(stdout, "[.] float object info\n  value: %f\n", PyFloat_AsDouble(p));
}
