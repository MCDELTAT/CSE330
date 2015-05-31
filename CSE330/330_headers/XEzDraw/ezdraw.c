


/*
 * ezdraw.c   ($Header: /home/kreiner/src/ftsoft/ft_XEzDraw/XEzDraw/RCS/ezdraw.c,v 1.9 2000/11/02 16:28:33 kreiner Exp $)
 *
 *
 * X11/unix implementation of EzDraw graphics library 
 * needed to run example programs from the book
 * Ford/Topp: "Introduction to Computing using C++ and Object Technology"
 * on X11/Unix boxes.
 *
 * dependencies:
 *    ezdraw.h  -- modified header file for graphics package 
 *                 based on the version supplied with the book
 *                 (use -D__unix compiler switch)
 *    X11 Window System (Xlib, X-Toolkit, Athena widgets)
 *
 * tested with with the following OS/compiler configurations: 
 *    FreeBSD 2.2.x and 3.1 / g++ (2.7.2.1)
 *    LINUX / g++
 *    Solaris7 / g++ (2.7.2)
 *    
 */
/*
 * Written by Christian Kreiner (kreiner@iti.tu-graz.ac.at)
 * Institute for Technical Informatics
 * Graz University of Technology, Austria
 *
 * You can do anything you want with this software, just don't say you wrote
 * it, and don't remove this notice.
 *
 * This software is provided "as is".
 *
 * The author supplies this software to be publicly redistributed on the
 * understanding that the author is not responsible for the correct
 * functioning of this software in any circumstances and is not liable for
 * any damages caused by this software.
 *
 * April 1999
 * Oct.  2000
 */


/*
** $Log: ezdraw.c,v $
** Revision 1.9  2000/11/02 16:28:33  kreiner
** integrated new features requested by Bill Ford:
** - new functions drawing unfilled shapes:
**     ezdDrawRectangleOutline(EZDFLOAT fX1, EZDFLOAT fY1, EZDFLOAT fX2, EZDFLOAT fY2);
**     ezdDrawCircleOutline(EZDFLOAT fX, EZDFLOAT fY, EZDFLOAT fR);
**     ezdDrawPolygonOutline(EZDULONG lCount, EZDCLPFLOAT pfXarray, EZDCLPFLOAT pfYarray);
** - new function drawing (horizontally) centered texts:
**     ezdDrawTextCentered(EZDLPCHAR szText, EZDFLOAT fX, EZDFLOAT fY);
**
*/

#ifdef __cplusplus
extern "C" 
{
#endif

static char *sid = "$Header: /home/kreiner/src/ftsoft/ft_XEzDraw/XEzDraw/RCS/ezdraw.c,v 1.9 2000/11/02 16:28:33 kreiner Exp $";

#include <ezdraw.h> /* include original header supplied with Ford/Topp book */

#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Simple.h>
/*#include <X11/Xaw/Viewport.h>/**/


/*** standard background  *********/

#define EZDBACKGROUND ezdWhite

/*** drawing coordinate to pixel coordinate factor  *********/

#define MAG 40.0



static XtAppContext	app_context;
static Display		*display;
static Widget 		ezshell;
static Widget 		vp;
static GC			mygc;



static char 		debug=0;
#define dprintf	 	if(debug)printf		


/*****************************************************************/
/**** viewport size and coordinate system                    *****/
/*****************************************************************/

#define	F2C(fC)		((short)( (fC) * MAG ))
#define XCOO(fx)	F2C((fx)-originX+(originType==ezdCenter?(vpWidth/2.):0.))
#define YCOO(fy)	F2C((fy)-originY+(originType==ezdCenter?(vpHeight/2.):0.))

static double	originX = 0;
static double	originY = 0;
static ezdOrigin	originType = ezdAtPoint;
static double	vpWidth = 10.0;
static double	vpHeight = 8.0;

EZDFLOAT EZDEXTERNAL ezdGetOriginX() { return originX; }
EZDFLOAT EZDEXTERNAL ezdGetOriginY() { return originY; }
ezdOrigin EZDEXTERNAL ezdGetOriginType() { return originType; }
EZDBOOL EZDEXTERNAL ezdSetOriginType(EZDINT iMode) 
{ 
	originType = (ezdOrigin)iMode;
	return EZDTRUE;
}

EZDBOOL EZDEXTERNAL ezdSetOrigin(EZDFLOAT fX, EZDFLOAT fY, ezdOrigin Origin)
{
	originX = fX;
	originY = fY;
	originType = Origin;
	return TRUE;
}

EZDFLOAT EZDEXTERNAL ezdGetViewportWidth() { return vpWidth;}
EZDFLOAT EZDEXTERNAL ezdGetViewportHeight() { return vpHeight;}
EZDBOOL EZDEXTERNAL ezdSetViewport(EZDFLOAT fX, EZDFLOAT fY)
{
	Arg viewportArgs[2];

	XtSetArg(viewportArgs[0], XtNheight,F2C(ezdGetViewportHeight()));
	XtSetArg(viewportArgs[1], XtNwidth,	F2C(ezdGetViewportWidth()));
	XtSetValues(vp,viewportArgs,XtNumber(viewportArgs));

	return TRUE;
}
ezdMapMode EZDEXTERNAL ezdGetMapMode()
	{printf("ezdGetMapMode() not implemented\n");}
EZDBOOL EZDEXTERNAL ezdSetMapMode(EZDINT iMode)
	{printf("ezdSetMapMode() not implemented\n");}
EZDBOOL EZDEXTERNAL ezdGetForceAspect()
	{printf("ezdGetForceAspect() not implemented\n");}
EZDBOOL EZDEXTERNAL ezdSetForceAspect(EZDBOOL bForce)
	{printf("ezdSetForceAspect() not implemented\n");}


/***********************************************/
/*** drawing color allocation & selection  *****/
/***********************************************/

#define EZDCOLORS	16	 /* align with color enumeration in ezdraw.h ! */

static unsigned int ezdcol(EZDCOLORVAL color)
{
	static char colnum = 0;
	static struct {
		EZDCOLORVAL	ezcol;
		XColor		xcol;
	} ezcols[EZDCOLORS];

	char colname[16];
	Colormap cmap;
	int i;


	for( i=0; i<colnum ; i++) {
		if ( ezcols[i].ezcol == color) 
			return ezcols[i].xcol.pixel;
	}

	/** allocate new XColor **/

	cmap = DefaultColormap(display,DefaultScreen(display));
	sprintf(colname,"#%02x%02x%02x",
			color&0xff, (color/0x100)&0xff,(color/0x10000)&0xff);

	if (i < EZDCOLORS &&
		XParseColor(display,cmap,colname,&(ezcols[i].xcol))
		&&
		XAllocColor(display,cmap, &(ezcols[i].xcol))) {

		ezcols[i].ezcol = color;
		++ colnum;
		dprintf("ezdcol new %s (No. %d)\n",colname,i);      
		return ezcols[i].xcol.pixel;    
	}
	else {
		printf("ezdcol %s failed\n",colname);      
	}

	return XBlackPixel(display,DefaultScreen(display));
}


static EZDCOLORVAL current_color;


EZDCOLORVAL EZDEXTERNAL ezdSetColor(EZDCOLORVAL color)
{
	EZDCOLORVAL 	last_color;

	dprintf("ezdSetColor %06x \n",color);

	last_color = current_color;
	current_color = color;

	return last_color;
}

static unsigned int ezdXbgnd = 0;  /* X11 background color */


/**********************************/
/*** graphic objects management ***/
/**********************************/

#define EZMAXHDL	10000 	/* object limit */


typedef	enum 	{
		ezdPoint,
		ezdLine,
		ezdRect,
		ezdCirc,
		ezdText,
		ezdPoly,
		}	ezdType;

typedef struct {
	short	x,y;
	unsigned short width,height;
	unsigned len;
	char	*txt;
}	xtext;

typedef struct {
	char			outline;
	unsigned int	npoints;
	XPoint			*points;
}	xpoly;

typedef struct {
	char		outline;
	XRectangle	rect;
}	xrectangle;

typedef struct {
	char		outline;
	XArc		arc;
}	xarc;

typedef struct {
	unsigned 	int 	id;
	ezdType		typ;
	unsigned int	xcolor;	
	union 	{
		XSegment	seg;
		xrectangle	rect;
		xarc		arc;
		xtext		text;
		xpoly		poly;
		XPoint		point;
		}	xobj;
	char		*auxBuf;
} ezdHandle;


static int newid = (EZMAXHDL-1);
static ezdHandle *ezdHdList[EZMAXHDL+1];

static ezdHandle *getHandle(unsigned int id)
{
	if ( ezdHdList[id-1] != NULL && ezdHdList[id-1]->id == id ) {
		return ezdHdList[id-1];
	} 
	return NULL;
}

static Bool destroyHandle(unsigned int id)
{
	ezdHandle *hdl = getHandle(id);
	Bool	result = FALSE;

	if ( hdl != NULL ) {
		XtFree(hdl->auxBuf);
		XtFree((char*)(hdl));
		result = TRUE;
	} 
	ezdHdList[id-1] = NULL;	
	return result;
}

#define SLOPPYHANDLES


static ezdHandle *newHandle(unsigned int addSize)
{
	ezdHandle *nw;
	int i,id;

	for( i=0 ; i < EZMAXHDL; ++i) {
		id = ((i+newid+1)%EZMAXHDL);
#ifdef SLOPPYHANDLES
		if ( destroyHandle(id+1) ) {
			dprintf("thrash handle %d\n",id+1);
		};
#else
		if( ezdHdList[id] == NULL )
#endif
			{
			nw = XtNew(ezdHandle);
			if (nw==NULL) {
				printf ("cannot allocate graphic object (ezdHandle)\n");
				return NULL;
			}
			nw->auxBuf = NULL;
			if ( addSize != 0 ) {
				nw->auxBuf = XtCalloc(1,addSize);
				if (nw->auxBuf == NULL ) {
					XtFree((char*)nw);
					printf("cannot allocate graphic object (auxBuf)\n");
					return NULL;
				}
			}
			nw->id = id+1;
			ezdHdList[id] = nw;
			newid = id;
			return nw;
			break;
		}
	}
	printf ("cannot allocate graphic object (max. %d)\n",EZMAXHDL);
	exit(1);
	return NULL;
}

/*******************************************/
/*** draw & erase graphic objects      *****/
/*******************************************/


static EZDBOOL EZDEXTERNAL ezdDrawShape(EZDHANDLE hShape,Bool erase)
{
	ezdHandle *hdl = getHandle(hShape);


	if ( hdl != NULL ) {

		dprintf("ezdDrawShape %s %d \n",erase ? "erase":"", hShape);

		XSetForeground(display,mygc,erase ? ezdXbgnd : hdl->xcolor);

		if ( hdl->typ == ezdRect ) {
			if ( hdl->xobj.rect.outline ) 
				XDrawRectangles(display, XtWindow(vp),mygc,
								&hdl->xobj.rect.rect,1);
			else			
				XFillRectangles(display,XtWindow(vp),mygc,
								&hdl->xobj.rect.rect,1);
		} else 
		if ( hdl->typ == ezdCirc ) {
			if ( hdl->xobj.arc.outline ) 
				XDrawArcs(display, XtWindow(vp),mygc,&hdl->xobj.arc.arc,1);
			else			
				XFillArcs(display, XtWindow(vp),mygc,&hdl->xobj.arc.arc,1);
		} else 
		if (hdl->typ == ezdLine) {
			XDrawSegments(display, XtWindow(vp),mygc,&hdl->xobj.seg,1);
		} else 
		if (hdl->typ == ezdPoly) {
			if ( hdl->xobj.poly.outline ) 
				XDrawLines(display, XtWindow(vp),mygc,
					hdl->xobj.poly.points,hdl->xobj.poly.npoints,
					CoordModeOrigin);
			else
				XFillPolygon(display, XtWindow(vp),mygc,
					hdl->xobj.poly.points,hdl->xobj.poly.npoints,
					Complex,CoordModeOrigin);
		} else 
		if (hdl->typ == ezdLine) {
			XDrawPoints(display, XtWindow(vp),mygc,
					&hdl->xobj.point,1,CoordModeOrigin);
		} else 
		if (hdl->typ == ezdText) {
			XDrawString(display, XtWindow(vp),mygc,
					hdl->xobj.text.x,hdl->xobj.text.y,
					hdl->xobj.text.txt,strlen(hdl->xobj.text.txt));
		} else {
			printf("don't know how to draw shape %d type %d\n",
				hShape,	hdl->typ);
		}
		return hdl->id;
	};
	return 0;
}


EZDBOOL EZDEXTERNAL ezdDeleteShape(EZDHANDLE hShape)
{
	dprintf("ezdDeleteShape %d \n",hShape);

	if ( ezdDrawShape(hShape,TRUE) != 0 ) {
		destroyHandle(hShape);
		return EZDTRUE;
	};
	return EZDFALSE;
}

static void  _ezdReDrawShapes(Bool erase)
{
	int i,id;

	if (!erase) XClearWindow(display, XtWindow(vp));
	for( i = 0; i < EZMAXHDL; ++i) {
		id = (newid+i+1)%EZMAXHDL;
		if (erase) 	destroyHandle(id+1);
		else 		ezdDrawShape(id+1,FALSE);
	}
	if (erase) XClearWindow(display, XtWindow(vp));
}

static void  ezdReDrawShapes(_WidgetRec *, void *, _XEvent *, char *)
{
	_ezdReDrawShapes(FALSE);
}

EZDBOOL EZDEXTERNAL ezdClearDrawSurface()
{
	dprintf("ezdClearDrawSurface\n");
	_ezdReDrawShapes(TRUE);
	return EZDTRUE;
}



EZDHANDLE EZDEXTERNAL ezdDrawLine(EZDFLOAT fX1, EZDFLOAT fY1, EZDFLOAT fX2, EZDFLOAT fY2)
{
	ezdHandle *hdl = newHandle(0);
	if ( hdl == NULL ) return 0;

	dprintf("ezdDrawLine id %d\n",hdl->id);

	hdl->typ = ezdLine;
	hdl->xcolor = ezdcol(current_color);
	hdl->xobj.seg.x1 = XCOO(fX1);
	hdl->xobj.seg.y1 = YCOO(fY1);
	hdl->xobj.seg.x2 = XCOO(fX2);
	hdl->xobj.seg.y2 = YCOO(fY2);
	return ezdDrawShape(hdl->id,FALSE);
}

static
EZDHANDLE EZDEXTERNAL _ezdDrawRectangle(EZDFLOAT fX1, EZDFLOAT fY1, EZDFLOAT fX2, EZDFLOAT fY2, char outline)
{
	ezdHandle *hdl = newHandle(0);
	if ( hdl == NULL ) return 0;

	dprintf("ezdDrawRectangle id %d\n",hdl->id);

	hdl->typ = ezdRect;
	hdl->xcolor = ezdcol(current_color);
	hdl->xobj.rect.outline = outline;
	hdl->xobj.rect.rect.x = XCOO(fX1);
	hdl->xobj.rect.rect.y = YCOO(fY1);
	hdl->xobj.rect.rect.width = F2C(fX2-fX1);
	hdl->xobj.rect.rect.height = F2C(fY2-fY1);
	return ezdDrawShape(hdl->id,FALSE);
}

EZDHANDLE EZDEXTERNAL ezdDrawRectangle(EZDFLOAT fX1, EZDFLOAT fY1, EZDFLOAT fX2, EZDFLOAT fY2)
{	return _ezdDrawRectangle(fX1,fY1,fX2,fY2,0); }
EZDHANDLE EZDEXTERNAL ezdDrawRectangleOutline(EZDFLOAT fX1, EZDFLOAT fY1, EZDFLOAT fX2, EZDFLOAT fY2)
{	return _ezdDrawRectangle(fX1,fY1,fX2,fY2,1); }

static
EZDHANDLE EZDEXTERNAL _ezdDrawCircle(EZDFLOAT fX, EZDFLOAT fY, EZDFLOAT fR, char outline)
{
	ezdHandle *hdl = newHandle(0);
	if ( hdl  == NULL ) return 0;

	dprintf("ezdDrawCircle id %d\n",hdl->id);

	hdl->typ = ezdCirc;
	hdl->xcolor = ezdcol(current_color);
	hdl->xobj.arc.outline = outline;
	hdl->xobj.arc.arc.x = XCOO(fX-fR);
	hdl->xobj.arc.arc.y = YCOO(fY-fR);
	hdl->xobj.arc.arc.width = F2C(fR*2.);
	hdl->xobj.arc.arc.height = F2C(fR*2.);
	hdl->xobj.arc.arc.angle1 = 0;
	hdl->xobj.arc.arc.angle2 = 360*64;
	return ezdDrawShape(hdl->id,FALSE);
}
EZDHANDLE EZDEXTERNAL ezdDrawCircle(EZDFLOAT fX, EZDFLOAT fY, EZDFLOAT fR)
{ return _ezdDrawCircle( fX, fY, fR, 0); }
EZDHANDLE EZDEXTERNAL ezdDrawCircleOutline(EZDFLOAT fX, EZDFLOAT fY, EZDFLOAT fR)
{ return _ezdDrawCircle( fX, fY, fR, 1); }

EZDHANDLE EZDEXTERNAL ezdDrawPoint(EZDFLOAT fX, EZDFLOAT fY)
{
	ezdHandle *hdl = newHandle(0);
	if ( hdl == NULL ) return 0;

	dprintf("ezdDrawPoint id %d\n",hdl->id);

	hdl->typ = ezdPoint;
	hdl->xcolor = ezdcol(current_color);
	hdl->xobj.point.x = XCOO(fX);
	hdl->xobj.point.y = YCOO(fY);
	return ezdDrawShape(hdl->id,FALSE);
}

static 
EZDHANDLE EZDEXTERNAL _ezdDrawPolygon(EZDULONG lCount, EZDCLPFLOAT pfXarray, EZDCLPFLOAT pfYarray,char outline)
{
	ezdHandle *hdl;
	int cnt;

	hdl = newHandle(lCount*sizeof(XPoint));
	if ( hdl  == NULL ) return 0;

	dprintf("ezdDrawPolygon id %d\n",hdl->id);

	hdl->typ = ezdPoly;
	hdl->xcolor = ezdcol(current_color);
	hdl->xobj.poly.outline = outline;
	hdl->xobj.poly.points = (XPoint*)(hdl->auxBuf);
	hdl->xobj.poly.npoints = lCount;
	for(cnt = 0 ; cnt < lCount; ++cnt ) {
		hdl->xobj.poly.points[cnt].x = XCOO(pfXarray[cnt]);
		hdl->xobj.poly.points[cnt].y = YCOO(pfYarray[cnt]);
	}
	return ezdDrawShape(hdl->id,FALSE);
}

EZDHANDLE EZDEXTERNAL ezdDrawPolygon(EZDULONG lCount, EZDCLPFLOAT pfXarray, EZDCLPFLOAT pfYarray)
{ return _ezdDrawPolygon(lCount,  pfXarray, pfYarray, 0); }
EZDHANDLE EZDEXTERNAL ezdDrawPolygonOutline(EZDULONG lCount, EZDCLPFLOAT pfXarray, EZDCLPFLOAT pfYarray)
{ return _ezdDrawPolygon(lCount,  pfXarray, pfYarray, 1); }

static XID	font;

static 
EZDHANDLE EZDEXTERNAL _ezdDrawText(EZDLPCHAR szText, EZDFLOAT fX, EZDFLOAT fY, int centered)
{
	int	textlen;
	ezdHandle *hdl;
	XFontStruct	*font_struc;

	textlen = strlen(szText);
	hdl = newHandle(textlen+1);
	if ( hdl  == NULL ) return 0;
	

	hdl->typ = ezdText;
	hdl->xcolor = ezdcol(current_color);

	hdl->xobj.text.width = (unsigned short) 0;
	font_struc = XQueryFont(display, font);
	if (font_struc != NULL ) hdl->xobj.text.width = XTextWidth(font_struc, szText,textlen);

	hdl->xobj.text.x = XCOO(fX) - (centered ? (hdl->xobj.text.width/2) : 0) ;
	hdl->xobj.text.y = YCOO(fY);
	hdl->xobj.text.len = textlen;   
	hdl->xobj.text.height = (unsigned short) 0;   
	strcpy(hdl->xobj.text.txt = hdl->auxBuf,szText);

	dprintf("ezdDrawText id %d text %s font_struc %p width %d\n",hdl->id,
			szText, font_struc, hdl->xobj.text.width);

	return ezdDrawShape(hdl->id,FALSE);
}

EZDHANDLE EZDEXTERNAL ezdDrawText(EZDLPCHAR szText, EZDFLOAT fX, EZDFLOAT fY)
{ return _ezdDrawText( szText,  fX, fY, 0); }

EZDHANDLE EZDEXTERNAL ezdDrawTextCentered(EZDLPCHAR szText, EZDFLOAT fX, EZDFLOAT fY)
{ return _ezdDrawText( szText,  fX, fY, 1); }

/*****************************************************************/
/**** X11 event processing loop and interruptions            *****/
/*****************************************************************/

static Bool		doWait = FALSE;
static Bool 	terminateMainLoop = FALSE ;
static Bool		keyPressed = FALSE;

static void stopMainLoop()
{
	dprintf("stopMainLoop\n");
	terminateMainLoop = TRUE;
}


static void myMainLoop()
{
	XEvent event;

	XSync(display,FALSE);
	keyPressed = FALSE;
	terminateMainLoop = FALSE;
	while( ! terminateMainLoop  ) {
		XtAppProcessEvent(app_context,XtIMAll);
	}
	dprintf("mainloop exit\n");
	
}
static EZDCHAR	chr;


EZDCHAR EZDEXTERNAL ezdWaitForKeyPress()
{
	dprintf("ezdWaitForKeyPress\n");
	doWait = FALSE;
	myMainLoop();
	return chr;
}

EZDBOOL EZDEXTERNAL ezdKeyPress()
{
	dprintf("ezdKeyPress \n");

	keyPressed = FALSE;
	while(XtAppPending(app_context))
		XtAppProcessEvent(app_context,XtIMAll);
	return keyPressed;
}



EZDBOOL EZDEXTERNAL ezdWait(EZDUINT uiMiliseconds)
{
	dprintf("ezdWait %d\n", uiMiliseconds);
	doWait = TRUE;
	XtAppAddTimeOut(app_context, uiMiliseconds,
			stopMainLoop,(XtPointer)1);
	myMainLoop();
	doWait = FALSE;
	return EZDTRUE;
}


/**********************************************************/
/** initialize & cleanup                                 **/
/**********************************************************/


void EZDEXTERNAL ezdCleanUp(void)
{
	dprintf("ezdCleanUp\n");

#ifdef ___INFO
/*ezdSetViewport(20.0, 10.0);*/
	ezdSetOrigin(0.0,0.0,ezdAtPoint);
	ezdSetColor(ezdLightBlue);
	ezdDrawRectangle(0.0,0.0,10.0,8.0);
	ezdSetColor(ezdBlack);
	ezdDrawText("EzDraw X11 Version", 1.0,1.0);
	ezdDrawText("written by C.Kreiner (kreiner@iti.tu-graz.ac.at)", 1.0,2.0);
	ezdDrawText("Institute for Technical Informatics", 1.0,2.5);
	ezdDrawText("Graz Universtity of Technology, Austria", 1.0,3.0);
	ezdWait(500);
#endif
	ezdClearDrawSurface();

	XFreeGC(display,mygc);
	XtDestroyWidget(ezshell);
	terminateMainLoop = 1;
}


/****** action callbacks **********/

static  void EndAction(Widget w,XEvent* evp,String *params,Cardinal *num_params)
{
	dprintf("view_cb\n");
	keyPressed = TRUE;
	if (!doWait) stopMainLoop();
}

static XtActionsRec actions[] =
{
  /* {name, procedure}, */
    {"end",        EndAction},
};


/****** initialize !  **********/

EZDBOOL EZDEXTERNAL ezdInitialize(void)
{

	{
	/* application init */
		char *args = "EZDRAW";
		int argc = 1;


		XtToolkitInitialize();

		app_context = XtCreateApplicationContext();
		XtAppAddActions(app_context,actions,XtNumber(actions));

		display = XtOpenDisplay(app_context,NULL,NULL,"EZDRAW",NULL,0,
							&argc,&args);

		ezshell = XtAppCreateShell(NULL,"EZDRAW",applicationShellWidgetClass,
				display,(ArgList) NULL,(Cardinal)0);

		font = XLoadFont(display,"fixed");
		/*font_struc = XQueryFont(display,font);*/

	};

	ezdSetColor(EZDBACKGROUND);
	ezdXbgnd = ezdcol(EZDBACKGROUND);

	{
	/****** viewport **********/
		String Translations = "<Key>: end()\n";
		Arg viewportArgs[4];

		XtSetArg(viewportArgs[0], XtNheight,F2C(ezdGetViewportHeight()));
		XtSetArg(viewportArgs[1], XtNwidth,	F2C(ezdGetViewportWidth()));
		XtSetArg(viewportArgs[2], XtNbackground,ezdXbgnd);
		XtSetArg(viewportArgs[3], XtNallowShellResize,FALSE);

		vp = XtCreateManagedWidget("viewport",simpleWidgetClass,
			ezshell,viewportArgs,XtNumber(viewportArgs));	
		XtAugmentTranslations(vp,XtParseTranslationTable(Translations));

		XtAddEventHandler(vp,ExposureMask,FALSE,ezdReDrawShapes,NULL);
	}


	XtRealizeWidget(ezshell);

	ezdWait(10); /* let it settle */

	mygc = XCreateGC(display,XtWindow(ezshell),0,0);

	XSetFont(display,mygc,font);

	return (ezshell != NULL);
}


#ifdef __cplusplus
}
#endif
