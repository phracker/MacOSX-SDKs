/*

Copyright 1987, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <X11/Xaw/TemplateP.h>

/*
 * Class Methods
 */
static void TemplateInitialize(Widget, Widget, ArgList, Cardinal*);

/*
 * Prototypes
 */
static Bool TemplateFunction(TemplateWidget, int, int, Bool);

/*
 * Actions
 */
static void TemplateAction(Widget, XEvent*, String*, Cardinal*);

/*
 * Initialization
 */
#define offset(field) XtOffsetOf(TemplateRec, template.field)
static XtResource resources[] = {
/*{
    name,
    class,
    type,
    size,
    offset,
    default_type,
    default_addr
  },*/
  {
    XtNtemplateResource,
    XtCTemplateResource,
    XtRTemplateResource,
    sizeof(char*),
    offset(resource),
    XtRString,
    (XtPointer)"default"
  },
};
#undef offset

static XtActionsRec actions[] =
{
    /*{name,		procedure},*/
    {"template",	TemplateAction},
};

static char translations[] =
"<Key>:"	"template()\n"
;

#define Superclass	(&widgetClassRec)
TemplateClassRec templateClassRec = {
  /* core */
  {
    (WidgetClass)Superclass,		/* superclass */
    "Template",				/* class_name */
    sizeof(TemplateRec),		/* widget_size */
    NULL,				/* class_initialize */
    NULL,				/* class_part_initialize */
    False,				/* class_inited */
    TemplateInitialize,			/* initialize */
    NULL,				/* initialize_hook */
    XtInheritRealize,			/* realize */
    actions,				/* actions */
    XtNumber(actions),			/* num_actions */
    resources,				/* resources */
    XtNumber(resources),		/* num_resources */
    NULLQUARK,				/* xrm_class */
    True,				/* compress_motion */
    True,				/* compress_exposure */
    True,				/* compress_enterleave */
    False,				/* visible_interest */
    NULL,				/* destroy */
    NULL,				/* resize */
    NULL,				/* expose */
    NULL,				/* set_values */
    NULL,				/* set_values_hook */
    XtInheritSetValuesAlmost,		/* set_values_almost */
    NULL,				/* get_values_hook */
    NULL,				/* accept_focus */
    XtVersion,				/* version */
    NULL,				/* callback_private */
    translations,			/* tm_table */
    XtInheritQueryGeometry,		/* query_geometry */
    XtInheritDisplayAccelerator,	/* display_accelerator */
    NULL,				/* extension */
  },
  /* template */
  {
    NULL,				/* extension */
  }
};

WidgetClass templateWidgetClass = (WidgetClass)&templateClassRec;

/*
 * Implementation
 */
/*
 * Function:
 *	TemplateInitialize
 *
 * Parameters:
 *	request - requested widget
 *	w	- the widget
 *	args	- arguments
 *	num_args - number of arguments
 *
 * Description:
 *	Initializes widget instance.
 */
/*ARGSUSED*/
static void
TemplateInitialize(Widget request, Widget w, ArgList args, Cardinal *num_args)
{
    TemplateWidget tw = (TemplateWidget)w;

    tw->template.private = NULL;
}

/*
 * Function:
 *	TemplateFunction
 *
 * Parameters:
 *	tw    - template widget
 *	x     - x coordinate
 *	y     - y coordinate
 *	force - force action
 *
 * Description:
 *	This function does nothing.
 *
 * Return:
 *	Parameter force
 */
/*ARGSUSED*/
static Bool
TemplateFunction(TemplateWidget tw, int x, int y, Bool force)
{
    return (force);
}

/*
 * Function:
 *	TemplateAction
 *
 * Parameters:
 *	w	   - template widget
 *	event	   - event that caused this action
 *	params	   - parameters
 *	num_params - number of parameters
 *
 * Description:
 *	This function does nothing.
 */
/*ARGSUSED*/
static void
TemplateAction(Widget w, XEvent *event, String *params, Cardinal *num_params)
{
}
