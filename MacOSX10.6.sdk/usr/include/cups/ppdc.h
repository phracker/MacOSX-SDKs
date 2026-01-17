//
// "$Id: ppdc.h 1558 2009-06-10 19:21:50Z msweet $"
//
//   Definitions for the CUPS PPD Compiler.
//
//   Copyright 2007-2009 by Apple Inc.
//   Copyright 2002-2007 by Easy Software Products.
//
//   These coded instructions, statements, and computer programs are the
//   property of Apple Inc. and are protected by Federal copyright
//   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
//   which should have been included with this file.  If this file is
//   file is missing or damaged, see the license at "http://www.cups.org/".
//

#ifndef _PPDC_H_
#  define _PPDC_H_

//
// Include necessary headers...
//

#  include <cups/file.h>
#  include <stdlib.h>


//
// Macros...
//

#  define PPDC_NAME(s)	const char *class_name() { return (s); }


//
// Enumerations...
//

enum ppdcDrvType			//// Driver type
{
  PPDC_DRIVER_CUSTOM,			// Custom driver
  PPDC_DRIVER_PS,			// PostScript driver
  PPDC_DRIVER_ESCP,			// rastertoescpx driver
  PPDC_DRIVER_PCL,			// rastertopclx driver
  PPDC_DRIVER_LABEL,			// rastertolabel/rastertodymo driver
  PPDC_DRIVER_EPSON,			// rastertoepson driver
  PPDC_DRIVER_HP,			// rastertohp driver
  PPDC_DRIVER_MAX			// Number of driver types defined
};

enum ppdcFontStatus			//// Load status of font
{
  PPDC_FONT_ROM,			// Font is in ROM
  PPDC_FONT_DISK			// Font is on disk
};

enum ppdcOptSection			//// Option section
{
  PPDC_SECTION_ANY,			// AnySetup
  PPDC_SECTION_DOCUMENT,		// DocumentSetup
  PPDC_SECTION_EXIT,			// ExitServer
  PPDC_SECTION_JCL,			// JCLSetup
  PPDC_SECTION_PAGE,			// PageSetup
  PPDC_SECTION_PROLOG			// Prolog
};

enum ppdcOptType			//// Option type
{
  PPDC_BOOLEAN,				// True/false option
  PPDC_PICKONE,				// Single choice from list
  PPDC_PICKMANY				// Multiple choices from list
};

enum ppdcLineEnding			//// Line endings
{
  PPDC_LFONLY,				// LF only
  PPDC_CRONLY,				// CR only
  PPDC_CRLF				// CR + LF
};

enum ppdcCondFlags			//// Condition flags
{
  PPDC_COND_NORMAL = 0,			// Normal state
  PPDC_COND_SKIP = 1,			// Skip state
  PPDC_COND_SATISFIED = 2		// At least one condition satisfied
};


//
// Printer description data...
//

class ppdcShared			//// Shared Data Value
{
  private:

  int		use;			// Use count (delete when 0)

  public:

  ppdcShared();
  virtual ~ppdcShared();

  virtual const char *class_name() = 0;

  void		retain();
  void		release();
};

class ppdcArray				//// Shared Array
  : public ppdcShared
{
  public:

  int		count,			// Number of elements
		alloc,			// Allocated elements
		current;		// Current element
  ppdcShared	**data;			// Elements

  ppdcArray(ppdcArray *a = 0);
  ~ppdcArray();

  PPDC_NAME("ppdcArray")

  void		add(ppdcShared *d);
  ppdcShared	*first();
  ppdcShared	*next();
  void		remove(ppdcShared *d);
};

class ppdcString			//// Shared String
  : public ppdcShared
{
  public:

  char		*value;			// String value

  ppdcString(const char *v);
  ~ppdcString();

  PPDC_NAME("ppdcString")
};

class ppdcInteger			//// Shared integer
  : public ppdcShared
{
  public:

  int		*value;			// Integer value

  ppdcInteger(int *v) { value = v; }

  PPDC_NAME("ppdcInteger")
};

class ppdcMessage			//// Translation message
  : public ppdcShared
{
  public:

  ppdcString	*id,			// Translation ID
		*string;		// Translation string

  ppdcMessage(const char *i, const char *s);
  ~ppdcMessage();

  PPDC_NAME("ppdcMessage")
};

class ppdcCatalog			//// Translation catalog
  : public ppdcShared
{
  public:

  ppdcString	*locale;		// Name of locale
  ppdcString	*filename;		// Name of translation file
  ppdcArray	*messages;		// Array of translation messages

  ppdcCatalog(const char *l, const char *f = 0);
  ~ppdcCatalog();

  PPDC_NAME("ppdcCatalog")

  void		add_message(const char *id, const char *string = NULL);
  const char	*find_message(const char *id);
  int		load_messages(const char *f);
  int		save_messages(const char *f);
};

class ppdcAttr				//// Attribute
  : public ppdcShared
{
  public:

  ppdcString	*name,			// Name of attribute
		*selector,		// Selector string
		*text,			// Text string
		*value;			// Value string
  bool		localizable;		// Should this attribute be localized?

  ppdcAttr(const char *n, const char *s, const char *t, const char *v,
           bool loc = false);
  ~ppdcAttr();

  PPDC_NAME("ppdcAttr")
};

class ppdcFont				//// Shared Font
  : public ppdcShared
{
  public:

  ppdcString	*name,			// Font name
		*encoding,		// Font base encoding
		*version,		// Font version
		*charset;		// Font charset
  ppdcFontStatus status;		// Font status (ROM or Disk)

  ppdcFont(const char *n, const char *e, const char *v, const char *c,
           ppdcFontStatus s);
  ~ppdcFont();

  PPDC_NAME("ppdcFont")
};

class ppdcChoice			//// Option Choice
  : public ppdcShared
{
  public:

  ppdcString	*name,			// Name of choice
		*text,			// Human-readable text of choice
		*code;			// PS code of choice

  ppdcChoice(const char *n, const char *t, const char *c);
  ~ppdcChoice();

  PPDC_NAME("ppdcChoice")
};

class ppdcOption			//// Option
  : public ppdcShared
{
  public:

  ppdcOptType	type;			// Type of option
  ppdcString	*name,			// Name of option
		*text;			// Human-readable text of option
  ppdcOptSection section;		// Section for option code
  float		order;			// Order number
  ppdcArray	*choices;		// Choices
  ppdcString	*defchoice;		// Default choice

  ppdcOption(ppdcOptType ot, const char *n, const char *t, ppdcOptSection s,
             float o);
  ppdcOption(ppdcOption *o);
  ~ppdcOption();

  PPDC_NAME("ppdcOption")

  void		add_choice(ppdcChoice *c) { choices->add(c); }
  ppdcChoice	*find_choice(const char *n);
  void		set_defchoice(ppdcChoice *c);
};

class ppdcGroup			//// Group of Options
  : public ppdcShared
{
  public:

  ppdcString	*name,			// Name of option
		*text;			// Human-readable text of option
  ppdcArray	*options;		// Options

  ppdcGroup(const char *n, const char *t);
  ppdcGroup(ppdcGroup *g);
  ~ppdcGroup();

  PPDC_NAME("ppdcGroup")

  void		add_option(ppdcOption *o) { options->add(o); }
  ppdcOption	*find_option(const char *n);
};

class ppdcConstraint			//// Constraint
  : public ppdcShared
{
  public:

  ppdcString	*option1,		// First option
		*choice1,		// First choice
		*option2,		// Second option
		*choice2;		// Second choice

  ppdcConstraint(const char *o1, const char *c1, const char *o2,
		 const char *c2);
  ~ppdcConstraint();

  PPDC_NAME("ppdcConstraint")
};

class ppdcFilter			//// Filter Program
  : public ppdcShared
{
  public:

  ppdcString	*mime_type,		// MIME type
		*program;		// Filter program
  int		cost;			// Relative cost of filter

  ppdcFilter(const char *t, const char *p, int c);
  ~ppdcFilter();

  PPDC_NAME("ppdcFilter")
};

class ppdcMediaSize			//// Media Size
  : public ppdcShared
{
  public:

  ppdcString	*name,			// Name of size
		*text;			// Human-readable text
  float		width,			// Width in points
		length,			// Length in points
		left,			// Left limit in points
		bottom,			// Bottom limit in points
		right,			// Right limit in points
		top;			// Top limit in points
  ppdcString	*size_code,		// PageSize code, if any
		*region_code;		// PageRegion code, if any

  ppdcMediaSize(const char *n, const char *t, float w, float l,
                float lm, float bm, float rm, float tm,
		const char *sc = 0, const char *rc = 0);
  ~ppdcMediaSize();

  PPDC_NAME("ppdcMediaSize")
};

class ppdcProfile			//// Color Profile
  : public ppdcShared
{
  public:

  ppdcString	*resolution,		// Resolution name
		*media_type;		// Media type name
  float		density,		// Color profile density
		gamma,			// Color profile gamma
		profile[9];		// Color profile matrix

  ppdcProfile(const char *r, const char *m, float d, float g, const float *p);
  ~ppdcProfile();

  PPDC_NAME("ppdcProfile")
};

class ppdcSource;

class ppdcDriver			//// Printer Driver Data
  : public ppdcShared
{
  public:

  ppdcDrvType	type;			// Driver type
  ppdcArray	*copyright;		// Copyright strings
  ppdcString	*manufacturer,		// Manufacturer
		*model_name,		// Name of printer model
		*file_name,		// Output filename for PPD
		*pc_file_name,		// 8 character PC filename for PPD
		*version;		// Version number
  int		model_number,		// Model number for driver
		manual_copies,		// Do manual copies?
		color_device,		// Support color?
		throughput;		// Throughput in pages per minute
  ppdcArray	*attrs,			// Attributes
		*constraints,		// Constraints
		*filters,		// Filters
		*fonts,			// Fonts
		*groups,		// Option groups
		*profiles,		// Color profiles
		*sizes;			// Fixed sizes
  ppdcString	*default_font,		// Default font
		*default_size;		// Default size option
  int		variable_paper_size;	// Support variable sizes?
  ppdcString	*custom_size_code;	// Custom page size code, if any
  float		left_margin,		// Margins for device in points
		bottom_margin,
		right_margin,
		top_margin,
		max_width,		// Maximum width (points)
		max_length,		// Maximum length (points)
		min_width,		// Minimum width (points)
		min_length;		// Minimum length (points)

  ppdcDriver(ppdcDriver *d = 0);
  ~ppdcDriver();

  PPDC_NAME("ppdcDriver")

  void		add_attr(ppdcAttr *a) { attrs->add(a); }
  void		add_constraint(ppdcConstraint *c) { constraints->add(c); }
  void		add_copyright(const char *c) {
    		  copyright->add(new ppdcString(c));
		}
  void		add_filter(ppdcFilter *f) { filters->add(f); }
  void		add_font(ppdcFont *f) { fonts->add(f); }
  void		add_group(ppdcGroup *g) { groups->add(g); }
  void		add_profile(ppdcProfile *p) { profiles->add(p); }
  void		add_size(ppdcMediaSize *m) { sizes->add(m); }

  ppdcAttr	*find_attr(const char *k, const char *s);
  ppdcGroup	*find_group(const char *n);
  ppdcOption	*find_option(const char *n);
  ppdcOption	*find_option_group(const char *n, ppdcGroup **mg);

  void		set_custom_size_code(const char *c);
  void		set_default_font(ppdcFont *f);
  void		set_default_size(ppdcMediaSize *m);
  void		set_file_name(const char *f);
  void		set_manufacturer(const char *m);
  void		set_model_name(const char *m);
  void		set_pc_file_name(const char *f);
  void		set_version(const char *v);

  int		write_ppd_file(cups_file_t *fp, ppdcCatalog *catalog,
		               ppdcArray *locales, ppdcSource *src,
			       ppdcLineEnding le);
};

class ppdcVariable			//// Variable Definition
  : public ppdcShared
{
  public:

  ppdcString	*name,			// Name of variable
		*value;			// Value of variable

  ppdcVariable(const char *n, const char *v);
  ~ppdcVariable();

  PPDC_NAME("ppdcVariable")

  void		set_value(const char *v);
};

class ppdcFile				//// File
{
  public:

  cups_file_t	*fp;			// File pointer
  const char	*filename;		// Filename
  int		line;			// Line in file

  ppdcFile(const char *f, cups_file_t *ffp = (cups_file_t *)0);
  ~ppdcFile();

  int		get();
  int		peek();
};

class ppdcSource			//// Source File
  : public ppdcShared
{
  public:

  static ppdcArray *includes;		// Include directories
  static const char *driver_types[];	// Driver types

  ppdcString	*filename;		// Filename
  ppdcArray	*base_fonts,		// Base fonts
		*drivers,		// Printer drivers
		*po_files,		// Message catalogs
		*sizes,			// Predefined media sizes
		*vars;			// Defined variables
  int		cond_state,		// Cummulative conditional state
		*cond_current,		// Current #if state
		cond_stack[101];	// #if state stack


  ppdcSource(const char *f = 0, cups_file_t *ffp = (cups_file_t *)0);
  ~ppdcSource();

  PPDC_NAME("ppdcSource")

  static void	add_include(const char *d);
  ppdcDriver	*find_driver(const char *f);
  static char	*find_include(const char *f, const char *base, char *n,
			      int nlen);
  ppdcCatalog	*find_po(const char *l);
  ppdcMediaSize	*find_size(const char *s);
  ppdcVariable	*find_variable(const char *n);
  ppdcAttr	*get_attr(ppdcFile *fp, bool loc = false);
  int		get_boolean(ppdcFile *fp);
  ppdcChoice	*get_choice(ppdcFile *fp);
  ppdcChoice	*get_color_model(ppdcFile *fp);
  int		get_color_order(const char *co);
  ppdcProfile	*get_color_profile(ppdcFile *fp);
  int		get_color_space(const char *cs);
  ppdcConstraint *get_constraint(ppdcFile *fp);
  ppdcMediaSize	*get_custom_size(ppdcFile *fp);
  void		get_duplex(ppdcFile *fp, ppdcDriver *d);
  ppdcFilter	*get_filter(ppdcFile *fp);
  float		get_float(ppdcFile *fp);
  ppdcFont	*get_font(ppdcFile *fp);
  ppdcChoice	*get_generic(ppdcFile *fp, const char *keyword,
		             const char *tattr, const char *nattr);
  ppdcGroup	*get_group(ppdcFile *fp, ppdcDriver *d);
  ppdcOption	*get_installable(ppdcFile *fp);
  int		get_integer(const char *v);
  int		get_integer(ppdcFile *fp);
  float		get_measurement(ppdcFile *fp);
  ppdcOption	*get_option(ppdcFile *fp, ppdcDriver *d, ppdcGroup *g);
  ppdcCatalog	*get_po(ppdcFile *fp);
  ppdcChoice	*get_resolution(ppdcFile *fp);
  ppdcProfile	*get_simple_profile(ppdcFile *fp);
  ppdcMediaSize	*get_size(ppdcFile *fp);
  char		*get_token(ppdcFile *fp, char *buffer, int buflen);
  ppdcVariable	*get_variable(ppdcFile *fp);
  int		import_ppd(const char *f);
  int		quotef(cups_file_t *fp, const char *format, ...);
  void		read_file(const char *f, cups_file_t *ffp = (cups_file_t *)0);
  void		scan_file(ppdcFile *fp, ppdcDriver *td = 0, bool inc = false);
  ppdcVariable	*set_variable(const char *name, const char *value);
  int		write_file(const char *f);
};


#endif // !_PPDC_H_

//
// End of "$Id: ppdc.h 1558 2009-06-10 19:21:50Z msweet $".
//
