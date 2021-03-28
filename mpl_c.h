#ifndef _MPL_C_H
#define _MPL_C_H

#include <Python.h>

#ifndef WITHOUT_NUMPY
#   define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#   include <numpy/arrayobject.h>
#endif

#if PY_MAJOR_VERSION >=3
#   define PyString_FromString PyUnicode_FromString
#   define PyInt_FromLong PyLong_FromLong
#endif

typedef struct _MPL_Kwargs
{
    char** key;
    char** value;
    size_t len;
} MPL_Kwargs;

MPL_Kwargs MPL_Kwargs_New(const size_t len)
{
    
}

enum _MPL_Callable_Enum
{
    _MPL_PyPlot_Show,
    _MPL_PyPlot_Close,
    _MPL_PyPlot_Draw,
    _MPL_PyPlot_Pause,
    _MPL_PyPlot_Save,
    _MPL_PyPlot_Figure,
    _MPL_PyPlot_Fignum_Exists,
    _MPL_PyPlot_Plot,
    _MPL_PyPlot_Quiver,
    _MPL_PyPlot_Semilogx,
    _MPL_PyPlot_Semilogy,
    _MPL_PyPlot_Loglog,
    _MPL_PyPlot_Fill,
    _MPL_PyPlot_Fill_between,
    _MPL_PyPlot_Hist,
    _MPL_PyPlot_Imshow,
    _MPL_PyPlot_Scatter,
    _MPL_PyPlot_Subplot,
    _MPL_PyPlot_Subplot2grid,
    _MPL_PyPlot_Legend,
    _MPL_PyPlot_Xlim,
    _MPL_PyPlot_Ion,
    _MPL_PyPlot_Ginput,
    _MPL_PyPlot_Ylim,
    _MPL_PyPlot_Title,
    _MPL_PyPlot_Axis,
    _MPL_PyPlot_Xlabel,
    _MPL_PyPlot_Ylabel,
    _MPL_PyPlot_Xticks,
    _MPL_PyPlot_Yticks,
    _MPL_PyPlot_Tick_params,
    _MPL_PyPlot_Grid,
    _MPL_PyPlot_Clf,
    _MPL_PyPlot_Errorbar,
    _MPL_PyPlot_Annotate,
    _MPL_PyPlot_Tight_layout,
    _MPL_PyPlot_Stem,
    _MPL_PyPlot_Xkcd,
    _MPL_PyPlot_Text,
    _MPL_PyPlot_Suptitle,
    _MPL_PyPlot_Bar,
    _MPL_PyPlot_Subplots_Adjust,
    _MPL_ColorMap
};

static PyObject* _MPL_Callable_List[44];
static PyObject* _MPL_Empty_Tuple;

PyObject* _MPL_Import(PyObject* module, const char* fname)
{
    PyObject* pyfunc = PyObject_GetAttrString(module, fname);

    if (!pyfunc) return NULL;
    if (!PyFunction_Check(pyfunc)) return NULL;

    return pyfunc;
}

#ifndef WITHOUT_NUMPY
#   if PY_MAJOR_VERSION >= 3
void* _MPL_Import_Numpy()
{
    import_array();
    return NULL;
}
#   else
void _MPL_Import_Numpy()
{
    import_array();
}
#endif
#endif


int MPL_Initialize()
{
    #if PY_MAJOR_VERSION >= 3
    wchar_t PyPname[] = L"MPL_Embed";
    #else
    char PyPname[] = "MPL_Embed";
    #endif

    Py_SetProgramName(PyPname);
    Py_Initialize();

    #ifndef WITHOUT_NUMPY
    _MPL_Import_Numpy();
    #endif

    PyObject* pystring_matplotlib = PyString_FromString("matplotlib");
    PyObject* pystring_pyplot = PyString_FromString("matplotlib.pyplot");
    PyObject* pystring_colormap = PyString_FromString("matplotlib.cm");
    PyObject* pystring_pylab = PyString_FromString("pylab");
    if (!pystring_matplotlib || !pystring_pyplot || !pystring_colormap || !pystring_pylab) return 0x01;
    
    PyObject* matplotlib = PyImport_Import(pystring_matplotlib);
    Py_DECREF(pystring_matplotlib);
    if (!matplotlib) return 0x02;

    // matplotlib.use() must be called *before* pylab, matplotlib.pyplot,
    // or matplotlib.backends is imported for the first time
    PyObject_CallMethod(matplotlib, "use", "s");

    PyObject* pyplot = PyImport_Import(pystring_pyplot);
    Py_DECREF(pystring_pyplot);
    if (!pyplot) return 0x03;

    _MPL_Callable_List[_MPL_ColorMap] = PyImport_Import(pystring_colormap);
    Py_DECREF(pystring_colormap);
    if (!_MPL_Callable_List[_MPL_ColorMap]) return 0x04;

    PyObject* pylab = PyImport_Import(pystring_pylab);
    Py_DECREF(pystring_pylab);
    if (!pylab) return 0x05;

    _MPL_Callable_List[_MPL_PyPlot_Show] = _MPL_Import(matplotlib, "show");
    _MPL_Callable_List[_MPL_PyPlot_Close] = _MPL_Import(matplotlib, "close");
    _MPL_Callable_List[_MPL_PyPlot_Draw] = _MPL_Import(matplotlib, "draw");
    _MPL_Callable_List[_MPL_PyPlot_Pause] = _MPL_Import(matplotlib, "pause");
    _MPL_Callable_List[_MPL_PyPlot_Save] = _MPL_Import(matplotlib, "save");
    _MPL_Callable_List[_MPL_PyPlot_Figure] = _MPL_Import(matplotlib, "figure");
    _MPL_Callable_List[_MPL_PyPlot_Fignum_Exists] = _MPL_Import(matplotlib, "fignum_exists");
    _MPL_Callable_List[_MPL_PyPlot_Plot] = _MPL_Import(matplotlib, "plot");
    _MPL_Callable_List[_MPL_PyPlot_Quiver] = _MPL_Import(matplotlib, "quiver");
    _MPL_Callable_List[_MPL_PyPlot_Semilogx] = _MPL_Import(matplotlib, "semilogx");
    _MPL_Callable_List[_MPL_PyPlot_Semilogy] = _MPL_Import(matplotlib, "semilogy");
    _MPL_Callable_List[_MPL_PyPlot_Loglog] = _MPL_Import(matplotlib, "loglog");
    _MPL_Callable_List[_MPL_PyPlot_Fill] = _MPL_Import(matplotlib, "fill");
    _MPL_Callable_List[_MPL_PyPlot_Fill_between] = _MPL_Import(matplotlib, "fill_between");
    _MPL_Callable_List[_MPL_PyPlot_Hist] = _MPL_Import(matplotlib, "hist");
    _MPL_Callable_List[_MPL_PyPlot_Imshow] = _MPL_Import(matplotlib, "imshow");
    _MPL_Callable_List[_MPL_PyPlot_Scatter] = _MPL_Import(matplotlib, "scatter");
    _MPL_Callable_List[_MPL_PyPlot_Subplot] = _MPL_Import(matplotlib, "subplot");
    _MPL_Callable_List[_MPL_PyPlot_Subplot2grid] = _MPL_Import(matplotlib, "subplot2grid");
    _MPL_Callable_List[_MPL_PyPlot_Legend] = _MPL_Import(matplotlib, "legend");
    _MPL_Callable_List[_MPL_PyPlot_Xlim] = _MPL_Import(matplotlib, "xlim");
    _MPL_Callable_List[_MPL_PyPlot_Ion] = _MPL_Import(matplotlib, "ion");
    _MPL_Callable_List[_MPL_PyPlot_Ginput] = _MPL_Import(matplotlib, "ginput");
    _MPL_Callable_List[_MPL_PyPlot_Ylim] = _MPL_Import(matplotlib, "ylim");
    _MPL_Callable_List[_MPL_PyPlot_Title] = _MPL_Import(matplotlib, "title");
    _MPL_Callable_List[_MPL_PyPlot_Axis] = _MPL_Import(matplotlib, "axis");
    _MPL_Callable_List[_MPL_PyPlot_Xlabel] = _MPL_Import(matplotlib, "xlabel");
    _MPL_Callable_List[_MPL_PyPlot_Ylabel] = _MPL_Import(matplotlib, "ylabel");
    _MPL_Callable_List[_MPL_PyPlot_Xticks] = _MPL_Import(matplotlib, "xticks");
    _MPL_Callable_List[_MPL_PyPlot_Yticks] = _MPL_Import(matplotlib, "yticks");
    _MPL_Callable_List[_MPL_PyPlot_Tick_params] = _MPL_Import(matplotlib, "tick_params");
    _MPL_Callable_List[_MPL_PyPlot_Grid] = _MPL_Import(matplotlib, "grid");
    _MPL_Callable_List[_MPL_PyPlot_Clf] = _MPL_Import(matplotlib, "clf");
    _MPL_Callable_List[_MPL_PyPlot_Errorbar] = _MPL_Import(matplotlib, "errorbar");
    _MPL_Callable_List[_MPL_PyPlot_Annotate] = _MPL_Import(matplotlib, "annotate");
    _MPL_Callable_List[_MPL_PyPlot_Tight_layout] = _MPL_Import(matplotlib, "tight_layout");
    _MPL_Callable_List[_MPL_PyPlot_Stem] = _MPL_Import(matplotlib, "stem");
    _MPL_Callable_List[_MPL_PyPlot_Xkcd] = _MPL_Import(matplotlib, "xkcd");
    _MPL_Callable_List[_MPL_PyPlot_Text] = _MPL_Import(matplotlib, "text");
    _MPL_Callable_List[_MPL_PyPlot_Suptitle] = _MPL_Import(matplotlib, "suptitle");
    _MPL_Callable_List[_MPL_PyPlot_Bar] = _MPL_Import(matplotlib, "ba");

    #ifndef WITHOUT_NUMPY
    _MPL_Callable_List[_MPL_PyPlot_Imshow] = _MPL_Import(matplotlib, "imshow");
    #endif

    _MPL_Empty_Tuple = PyTuple_New(0);

    return 0x00;
}

int MPL_Finalize()
{
    for (int i = 0; i < 44; ++i) Py_DECREF(_MPL_Callable_List[i]);
    Py_DECREF(_MPL_Empty_Tuple);
    Py_Finalize();

    return 0;
}

inline int MPL_Annotate(const char* annotation, double x, double y)
{
    PyObject* xy = PyTuple_New(2);
    PyObject* str = PyString_FromString(annotation);

    PyTuple_SetItem(xy, 0, PyFloat_FromDouble(x));
    PyTuple_SetItem(xy, 1, PyFloat_FromDouble(y));

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, str);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "xy", xy);

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Annotate], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

#ifndef WITHOUT_NUMPY
PyObject* _MPL_Get_Array(double* v, const size_t len)
{
    npy_intp pyarraysize = len;
    PyObject* pyarray = PyArray_SimpleNewFromData(1, &pyarraysize, NPY_DOUBLE, (void*)v);
    return pyarray;
}
#else
PyObject* _MPL_Get_Array(const double* v, const size_t len)
{
    PyObject* pyarray = PyList_New(len);
    for (int i = 0; i < len; ++i) PyList_SetItem(pyarray, i, PyFloat_FromDouble(v[i]));
    return pyarray;
}
#endif

#ifndef WITHOUT_NUMPY
PyObject* _MPL_Get_2DArray(double* m, const size_t rows, const size_t cols)
{
    npy_intp pyarraysize[2] = {rows, cols};
    PyObject* pyarray = PyArray_SimpleNewFromData(2, pyarraysize, NPY_DOUBLE, (void*)m);
    return pyarray;
}
#else
PyObject* _MPL_Get_2DArray(double* m, const size_t rows, const size_t cols)
{
    PyObject* pyarray = Pylist_new(rows);
    PyObject* row = (PyObject*)malloc(sizeof(PyObject*) * rows);
    for (size_t i = 0; i < rows, ++i)
    {
        size_t curhome = i * rows;
        row[i] = PyList_new(cols);
        for (size_t j = 0; j < cols; ++j)
        {
            PyList_SetItem(row[i], j, PyFloat_FromDouble(m[curhome + j]));
        }
        PyList_SetItem(pyarray, i, row[i]);
    }
    return pyarray;
}
#endif

int MPL_Plot(double* x, const size_t xlen, double* y, const size_t ylen, MPL_Kwargs* keywords)
{
    assert(xlen == ylen);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);

    PyObject* kwargs = PyDict_New();
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Plot], args, kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Plot_Label(double* x, const size_t xlen, double* y, const size_t ylen, const char* label, MPL_Kwargs* keywords)
{
    MPL_Kwargs kwargs;
    size_t kwargs_len;
    
    if (keywords)
    {

    }
    else
    {
        
    }
    
}

int MPL_Plot_Y_Only(double* y, const size_t ylen, MPL_Kwargs* keywords)
{
    double* x = (double*)malloc(sizeof(double)*ylen);
    int res = MPL_Plot(x, ylen, y, ylen, keywords);
    free(x);
    return res;
}

int MPL_Plot_Surface(
    double* x, const size_t xrows, const size_t xcols,
    double* y, const size_t yrows, const size_t ycols,
    double* z, const size_t zrows, const size_t zcols, MPL_Kwargs* keywords
)
{
    PyObject* pystring_mpl_toolkits = PyString_FromString("mpl_toolkits");
    PyObject* pystring_mplot3d = PyString_FromString("mpl_toolkits.mplot3d");
    if (!pystring_mpl_toolkits || !pystring_mplot3d) return 0x01;

    PyObject* mpl_toolkits = PyImport_Import(pystring_mpl_toolkits);
    Py_DECREF(pystring_mpl_toolkits);
    if (!mpl_toolkits) return 0x02;

    PyObject* mplot3d = PyImport_Import(pystring_mplot3d);
    Py_DECREF(pystring_mplot3d);
    if (!mplot3d) return 0x03;

    assert(xrows == yrows == zrows);
    assert(xcols == ycols == zcols);

    PyObject* xm = _MPL_Get_2DArray(x, xrows, xcols);
    PyObject* ym = _MPL_Get_2DArray(y, yrows, ycols);
    PyObject* zm = _MPL_Get_2DArray(z, zrows, zcols);

    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, xm);
    PyTuple_SetItem(args, 1, ym);
    PyTuple_SetItem(args, 2, zm);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "rstride", PyInt_FromLong(1));
    PyDict_SetItemString(kwargs, "cstride", PyInt_FromLong(1));
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* fig = PyObject_CallObject(
        _MPL_Callable_List[_MPL_PyPlot_Figure], _MPL_Empty_Tuple
    );
    if (!fig) return 0x04;

    PyObject* gca_kwargs = PyDict_New();
    PyDict_SetItemString(gca_kwargs, "projection", PyString_FromString("3d"));

    PyObject* gca = PyObject_GetAttrString(fig, "gca");
    if (!gca) return 0x05;
    Py_INCREF(gca);
    PyObject* axis = PyObject_Call(gca, _MPL_Empty_Tuple, gca_kwargs);
    if (!axis) return 0x06;
    Py_DECREF(gca);
    Py_DECREF(gca_kwargs);

    PyObject* plot_surface = PyObject_GetAttrString(axis, "plot_surface");
    if (!plot_surface) return 0x07;
    Py_INCREF(plot_surface);
    
    PyObject* res = PyObject_Call(plot_surface, args, kwargs);
    if (!res) return 0x08;
    else Py_DECREF(res);
    Py_DECREF(plot_surface);
    Py_DECREF(axis);
    Py_DECREF(args);
    Py_DECREF(kwargs);

    return (int)res;
}

int MPL_Stem(double* x, const size_t xlen, double* y, const size_t ylen, MPL_Kwargs* keywords)
{
    assert(xlen == ylen);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);

    PyObject* kwargs = PyDict_New();
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }
    
    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Stem], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Fill(double* x, const size_t xlen, double* y, const size_t ylen, MPL_Kwargs* keywords)
{
    assert(xlen == ylen);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);

    PyObject* kwargs = PyDict_New();
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }
    
    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Fill], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Fill_between(
    double* x, const size_t xlen,
    double* y1, const size_t y1len,
    double* y2, const size_t y2len, MPL_Kwargs* keywords
)
{
    assert(xlen == y1len == y2len);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* y1v = _MPL_Get_Array(y1, y1len);
    PyObject* y2v = _MPL_Get_Array(y2, y2len);

    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, y1v);
    PyTuple_SetItem(args, 2, y2v);

    PyObject* kwargs = PyDict_New();
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }
    
    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Fill], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Hist(double* y, const size_t ylen, long bins, const char* color, double alpha, int cumulative)
{
    PyObject* yv = _MPL_Get_Array(y, ylen);

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, yv);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "bins", PyLong_FromLong(bins));
    PyDict_SetItemString(kwargs, "color", PyString_FromString("color"));
    PyDict_SetItemString(kwargs, "alpha", PyFloat_FromDouble(alpha));
    PyDict_SetItemString(kwargs, "cumulative", PyBool_FromLong(cumulative));

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Hist], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Scatter(
    double* x, const size_t xlen, double* y, const size_t ylen,
    double s, MPL_Kwargs* keywords
)
{
    assert(xlen == ylen);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "s", PyLong_FromLong(s));
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Scatter], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Bar(
    double* x, const size_t xlen, double* y, const size_t ylen,
    const char* ec, const char* ls, double lw,
    MPL_Kwargs* keywords
)
{
    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "ec", PyString_FromString(ec));
    PyDict_SetItemString(kwargs, "ls", PyString_FromString(ls));
    PyDict_SetItemString(kwargs, "lw", PyFloat_FromDouble(lw));
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Bar], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

inline int MPL_Subplots_Adjust(MPL_Kwargs* keywords)
{
    PyObject* args = PyTuple_New(0);

    PyObject* kwargs = PyDict_New();
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Subplots_Adjust], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Quiver(
    double* x, const size_t xlen, double* y, const size_t ylen,
    double* u, const size_t ulen, double* v, const size_t vlen, MPL_Kwargs* keywords
)
{
    assert(xlen == ylen == ulen == vlen);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);
    PyObject* uv = _MPL_Get_Array(u, ulen);
    PyObject* wv = _MPL_Get_Array(v, vlen);

    PyObject* args = PyTuple_New(4);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);
    PyTuple_SetItem(args, 2, uv);
    PyTuple_SetItem(args, 3, wv);

    PyObject* kwargs = PyDict_New();
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Quiver], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Semilogx(double* x, const size_t xlen, double* y, const size_t ylen, MPL_Kwargs* keywords)
{
    assert(xlen == ylen);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);

    PyObject* kwargs = PyDict_New();
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Semilogx], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Semilogy(double* x, const size_t xlen, double* y, const size_t ylen, MPL_Kwargs* keywords)
{
    assert(xlen == ylen);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);

    PyObject* kwargs = PyDict_New();
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Semilogy], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_LogLog(double* x, const size_t xlen, double* y, const size_t ylen, MPL_Kwargs* keywords)
{
    assert(xlen == ylen);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);

    PyObject* kwargs = PyDict_New();
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Loglog], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Errorbar(
    double* x, const size_t xlen, double* y, const size_t ylen,
    double* yerr, const size_t yerrlen, MPL_Kwargs* keywords
)
{
    assert(xlen == ylen == yerrlen);

    PyObject* xv = _MPL_Get_Array(x, xlen);
    PyObject* yv = _MPL_Get_Array(y, ylen);
    PyObject* yerrv = _MPL_Get_Array(yerr, yerrlen);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xv);
    PyTuple_SetItem(args, 1, yv);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "yerr", yerrv);
    if (keywords)
    {
        for (size_t i = 0; i < keywords->len; ++i)
        {
            PyDict_SetItemString(kwargs, keywords->key[i], PyString_FromString(keywords->value[i]));
        }
    }

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Errorbar], args, kwargs);
    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res) Py_DECREF(res);

    return (int) res;
}

int MPL_Text(double x, double y, const char* s = "")
{
    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, PyFloat_FromDouble(x));
    PyTuple_SetItem(args, 1, PyFloat_FromDouble(y));
    PyTuple_SetItem(args, 2, PyString_FromString(s));

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Text], args, NULL);
    Py_DECREF(args);
    if (res) Py_DECREF(res);

    return (int) res;
}

// @param number Default value is -1
int MPL_Figure(int number)
{
    PyObject* res;
    if (number == -1)
    {
        res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Figure], _MPL_Empty_Tuple, NULL);
    }
    else
    {
        assert(number > 0);

        PyObject* args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyLong_FromLong(number));
        res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Figure], args, NULL);
        Py_DECREF(args);
    }
    
    PyObject* fig = PyObject_GetAttrString(res, "number");
    if (!fig) return 0x01;
    int figNum = PyLong_AsLong(fig);

    Py_DECREF(res);
    Py_DECREF(fig);
    
    return figNum;
}

int MPL_Fignum_Exists(int number)
{
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyLong_FromLong(number));
    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Fignum_Exists], args, NULL);
    
    int flag = PyObject_IsTrue(res);
    Py_DECREF(res);
    Py_DECREF(args);

    return flag;
}

int MPL_Figure_Size(const size_t w, const size_t h)
{
    const size_t dpi = 100;

    PyObject* size = PyTuple_New(2);
    PyTuple_SetItem(size, 0, PyFloat_FromDouble((double)w / dpi));
    PyTuple_SetItem(size, 1, PyFloat_FromDouble((double)h / dpi));

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "figsize", size);
    PyDict_SetItemString(kwargs, "dpi", PyLong_FromSize_t(dpi));

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Figure], _MPL_Empty_Tuple, kwargs);
    if (res) Py_DECREF(res);
    Py_DecRef(kwargs);
    Py_DECREF(size);

    return (int)res;
}

int MPL_Legend()
{
    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Legend], _MPL_Empty_Tuple, NULL);
    if (res) Py_DECREF(res);

    return (int)res;
}

int MPL_Xlim(double min, double max)
{
    PyObject* pair = PyTuple_New(2);
    PyTuple_SetItem(pair, 0, PyFloat_FromDouble(min));
    PyTuple_SetItem(pair, 1, PyFloat_FromDouble(max));

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, pair);

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Xlim], args, NULL);
    if (res) Py_DECREF(res);
    Py_DECREF(args);
    Py_DECREF(pair);

    return (int)res;
}

int MPL_Ylim(double min, double max)
{
    PyObject* pair = PyTuple_New(2);
    PyTuple_SetItem(pair, 0, PyFloat_FromDouble(min));
    PyTuple_SetItem(pair, 1, PyFloat_FromDouble(max));

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, pair);

    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Ylim], args, NULL);
    if (res) Py_DECREF(res);
    Py_DECREF(args);
    Py_DECREF(pair);

    return (int)res;
}

double* MPL_Xlim_Get()
{
    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Xlim], _MPL_Empty_Tuple, NULL);
    PyObject* min = PyTuple_GetItem(res, 0);
    PyObject* max = PyTuple_GetItem(res, 1);

    double* pair = (double*)malloc(sizeof(double)*2);
    pair[0] = PyFloat_AsDouble(min);
    pair[1] = PyFloat_AsDouble(max);

    if (res) Py_DECREF(res);
    Py_DECREF(min);
    Py_DECREF(max);

    return pair;
}

double* MPL_Ylim_Get()
{
    PyObject* res = PyObject_Call(_MPL_Callable_List[_MPL_PyPlot_Ylim], _MPL_Empty_Tuple, NULL);
    PyObject* min = PyTuple_GetItem(res, 0);
    PyObject* max = PyTuple_GetItem(res, 1);

    double* pair = (double*)malloc(sizeof(double)*2);
    pair[0] = PyFloat_AsDouble(min);
    pair[1] = PyFloat_AsDouble(max);

    if (res) Py_DECREF(res);
    Py_DECREF(min);
    Py_DECREF(max);

    return pair;
}

#endif