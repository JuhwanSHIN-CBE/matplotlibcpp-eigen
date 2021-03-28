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

enum _MPL_Callable_Enum
{
    MPL_PyPlot_Show,
    MPL_PyPlot_Close,
    MPL_PyPlot_Draw,
    MPL_PyPlot_Pause,
    MPL_PyPlot_Save,
    MPL_PyPlot_Figure,
    MPL_PyPlot_Fignum_Exists,
    MPL_PyPlot_Plot,
    MPL_PyPlot_Quiver,
    MPL_PyPlot_Semilogx,
    MPL_PyPlot_Semilogy,
    MPL_PyPlot_Loglog,
    MPL_PyPlot_Fill,
    MPL_PyPlot_Fill_between,
    MPL_PyPlot_Hist,
    MPL_PyPlot_Imshow,
    MPL_PyPlot_Scatter,
    MPL_PyPlot_Subplot,
    MPL_PyPlot_Subplot2grid,
    MPL_PyPlot_Legend,
    MPL_PyPlot_Xlim,
    MPL_PyPlot_Ion,
    MPL_PyPlot_Ginput,
    MPL_PyPlot_Ylim,
    MPL_PyPlot_Title,
    MPL_PyPlot_Axis,
    MPL_PyPlot_Xlabel,
    MPL_PyPlot_Ylabel,
    MPL_PyPlot_Xticks,
    MPL_PyPlot_Yticks,
    MPL_PyPlot_Tick_params,
    MPL_PyPlot_Grid,
    MPL_PyPlot_Clf,
    MPL_PyPlot_Errorbar,
    MPL_PyPlot_Annotate,
    MPL_PyPlot_Tight_layout,
    MPL_PyPlot_Stem,
    MPL_PyPlot_Xkcd,
    MPL_PyPlot_Text,
    MPL_PyPlot_Suptitle,
    MPL_PyPlot_Bar,
    MPL_PyPlot_Subplots_Adjust,
    MPL_ColorMap
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

    _MPL_Callable_List[MPL_ColorMap] = PyImport_Import(pystring_colormap);
    Py_DECREF(pystring_colormap);
    if (!_MPL_Callable_List[MPL_ColorMap]) return 0x04;

    PyObject* pylab = PyImport_Import(pystring_pylab);
    Py_DECREF(pystring_pylab);
    if (!pylab) return 0x05;

    _MPL_Callable_List[MPL_PyPlot_Show] = _MPL_Import(matplotlib, "show");
    _MPL_Callable_List[MPL_PyPlot_Close] = _MPL_Import(matplotlib, "close");
    _MPL_Callable_List[MPL_PyPlot_Draw] = _MPL_Import(matplotlib, "draw");
    _MPL_Callable_List[MPL_PyPlot_Pause] = _MPL_Import(matplotlib, "pause");
    _MPL_Callable_List[MPL_PyPlot_Save] = _MPL_Import(matplotlib, "save");
    _MPL_Callable_List[MPL_PyPlot_Figure] = _MPL_Import(matplotlib, "figure");
    _MPL_Callable_List[MPL_PyPlot_Fignum_Exists] = _MPL_Import(matplotlib, "fignum_exists");
    _MPL_Callable_List[MPL_PyPlot_Plot] = _MPL_Import(matplotlib, "plot");
    _MPL_Callable_List[MPL_PyPlot_Quiver] = _MPL_Import(matplotlib, "quiver");
    _MPL_Callable_List[MPL_PyPlot_Semilogx] = _MPL_Import(matplotlib, "semilogx");
    _MPL_Callable_List[MPL_PyPlot_Semilogy] = _MPL_Import(matplotlib, "semilogy");
    _MPL_Callable_List[MPL_PyPlot_Loglog] = _MPL_Import(matplotlib, "loglog");
    _MPL_Callable_List[MPL_PyPlot_Fill] = _MPL_Import(matplotlib, "fill");
    _MPL_Callable_List[MPL_PyPlot_Fill_between] = _MPL_Import(matplotlib, "fill_between");
    _MPL_Callable_List[MPL_PyPlot_Hist] = _MPL_Import(matplotlib, "hist");
    _MPL_Callable_List[MPL_PyPlot_Scatter] = _MPL_Import(matplotlib, "scatter");
    _MPL_Callable_List[MPL_PyPlot_Subplot] = _MPL_Import(matplotlib, "subplot");
    _MPL_Callable_List[MPL_PyPlot_Subplot2grid] = _MPL_Import(matplotlib, "subplot2grid");
    _MPL_Callable_List[MPL_PyPlot_Legend] = _MPL_Import(matplotlib, "legend");
    _MPL_Callable_List[MPL_PyPlot_Xlim] = _MPL_Import(matplotlib, "xlim");
    _MPL_Callable_List[MPL_PyPlot_Ion] = _MPL_Import(matplotlib, "ion");
    _MPL_Callable_List[MPL_PyPlot_Ginput] = _MPL_Import(matplotlib, "ginput");
    _MPL_Callable_List[MPL_PyPlot_Ylim] = _MPL_Import(matplotlib, "ylim");
    _MPL_Callable_List[MPL_PyPlot_Title] = _MPL_Import(matplotlib, "title");
    _MPL_Callable_List[MPL_PyPlot_Axis] = _MPL_Import(matplotlib, "axis");
    _MPL_Callable_List[MPL_PyPlot_Xlabel] = _MPL_Import(matplotlib, "xlabel");
    _MPL_Callable_List[MPL_PyPlot_Ylabel] = _MPL_Import(matplotlib, "ylabel");
    _MPL_Callable_List[MPL_PyPlot_Xticks] = _MPL_Import(matplotlib, "xticks");
    _MPL_Callable_List[MPL_PyPlot_Yticks] = _MPL_Import(matplotlib, "yticks");
    _MPL_Callable_List[MPL_PyPlot_Tick_params] = _MPL_Import(matplotlib, "tick_params");
    _MPL_Callable_List[MPL_PyPlot_Grid] = _MPL_Import(matplotlib, "grid");
    _MPL_Callable_List[MPL_PyPlot_Clf] = _MPL_Import(matplotlib, "clf");
    _MPL_Callable_List[MPL_PyPlot_Errorbar] = _MPL_Import(matplotlib, "errorbar");
    _MPL_Callable_List[MPL_PyPlot_Annotate] = _MPL_Import(matplotlib, "annotate");
    _MPL_Callable_List[MPL_PyPlot_Tight_layout] = _MPL_Import(matplotlib, "tight_layout");
    _MPL_Callable_List[MPL_PyPlot_Stem] = _MPL_Import(matplotlib, "stem");
    _MPL_Callable_List[MPL_PyPlot_Xkcd] = _MPL_Import(matplotlib, "xkcd");
    _MPL_Callable_List[MPL_PyPlot_Text] = _MPL_Import(matplotlib, "text");
    _MPL_Callable_List[MPL_PyPlot_Suptitle] = _MPL_Import(matplotlib, "suptitle");
    _MPL_Callable_List[MPL_PyPlot_Bar] = _MPL_Import(matplotlib, "bar");

    #ifndef WITHOUT_NUMPY
    _MPL_Callable_List[MPL_PyPlot_Imshow] = _MPL_Import(matplotlib, "imshow");
    #endif
    
    _MPL_Empty_Tuple = PyTuple_New(0);

    return 0;
}




#endif