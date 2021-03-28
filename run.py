s = """MPL_PyPlot_Show,
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
    MPL_PyPlot_Bar"""

rest = """
    PyObject *s_python_colormap;
    PyObject *s_python_empty_tuple;"""
sl = s.split("\n")
for i in range(len(sl)): sl[i] = sl[i].strip()
for sen in sl:
    buff = sen
    print(f"_MPL_Callable_List[{sen[:-1]}] = _MPL_Import(matplotlib, \"{sen[11:-1].lower()}\");")