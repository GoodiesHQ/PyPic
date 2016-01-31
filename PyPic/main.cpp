#include "fi.h"
#include "include.h"

/*struct sortColors {
bool operator() (const colormask &c1, const colormask &c2){
return c1.second > c2.second;
}
};*/ // Unneeded

std::vector<colormask> getrgb(std::string fileName, int type) {
	std::vector<colormask> rgb; // = new std::vector<colormask>;
	FreeImage_Initialise(TRUE); /* Initialize the FreeImage library */
	FIBITMAP *img = FreeImage_Load(static_cast<FREE_IMAGE_FORMAT>(type), fileName.c_str());
	rgb.push_back(std::make_pair(PP_RED, FreeImage_GetRedMask(img)));
	rgb.push_back(std::make_pair(PP_GREEN, FreeImage_GetGreenMask(img)));
	rgb.push_back(std::make_pair(PP_BLUE, FreeImage_GetBlueMask(img)));
	FreeImage_Unload(img); /* Done with the FreeImage library */
	FreeImage_DeInitialise(); /* Done with the FreeImage library */
	/* Sort the RGB vector by most common to least common color before turning into a Python Dictionary */
	/* std::sort(rgb.begin(), rgb.end(), sortColors()); */
	// Except python dicts aren't sorted, so this is pointless...
	return rgb;
}

PyObject *getrgb_wrapper(PyObject *self, PyObject *args) {
	/* create python variables */
	char *cfileName;
	int type;
	/* parse python variables */
	if (!PyArg_ParseTuple(args, "si", &cfileName, &type))
		return NULL;

	std::string fileName(cfileName);
	std::vector<colormask> rgb = getrgb(fileName, type);

	PyDictObject *colorDict = (PyDictObject*)PyDict_New();

	for (auto c = rgb.begin(); c != rgb.end(); ++c) /* Set each extention as an elemnt in the dictionary */
		PyDict_SetItem(
			(PyObject*)colorDict,
			PyString_FromString(c->first.c_str()),
			PyInt_FromSize_t(c->second)
			);
	rgb.clear();
	return (PyObject*)colorDict;
	PyDictObject *n = (PyDictObject*)PyDict_New();
	return (PyObject*)n;
}

inline void init_extlist() {
	extensions = (PyDictObject*)PyDict_New();
	std::unordered_map<std::string, size_t> extmap = {
		{ "unknown", FIF_UNKNOWN },{ "bmp", FIF_BMP },{ "ico", FIF_ICO },{ "jpeg", FIF_JPEG },
		{ "jpg", FIF_JPEG },{ "jng", FIF_JNG },{ "koala", FIF_KOALA },{ "lbm", FIF_LBM },
		{ "iff", FIF_IFF },{ "mng", FIF_MNG },{ "pbm", FIF_PBM },{ "pbmraw", FIF_PBMRAW },
		{ "pcd", FIF_PCD },{ "pcx", FIF_PCX },{ "pgm", FIF_PGM },{ "pgmraw", FIF_PGMRAW },
		{ "png", FIF_PNG },{ "ppm", FIF_PPM },{ "ppmraw", FIF_PPMRAW },{ "ras", FIF_RAS },
		{ "targa", FIF_TARGA },{ "tiff", FIF_TIFF },{ "wbmp", FIF_WBMP },{ "psd", FIF_PSD },
		{ "cut", FIF_CUT },{ "xbm", FIF_XBM },{ "xpm", FIF_XPM },{ "dds", FIF_DDS },
		{ "gif", FIF_GIF },{ "hdr", FIF_HDR },{ "faxg3", FIF_FAXG3 },{ "sgi", FIF_SGI },
		{ "exr", FIF_EXR },{ "j2k", FIF_J2K },{ "jp2", FIF_JP2 },{ "pfm", FIF_PFM },
		{ "pict", FIF_PICT },{ "raw", FIF_RAW },{ "webp", FIF_WEBP },{ "jxr", FIF_JXR },
	};
	for (auto ext : extmap)
		PyDict_SetItem(
			(PyObject*)extensions,						// dictionary object
			PyString_FromString(ext.first.c_str()),		// item name
			PyInt_FromSize_t(ext.second)				// key value
		);
}

PyMethodDef pypic_methods[] = {
	{ "getrgb", (PyCFunction)getrgb_wrapper, METH_VARARGS, 0 },
	{ NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initpypic(void) {
	PyObject *m;
	m = Py_InitModule(MODULE_NAME, pypic_methods);
	if (m == NULL)
		return;
	init_extlist();
	PyModule_AddObject(m, "extensions", (PyObject*)extensions);
}