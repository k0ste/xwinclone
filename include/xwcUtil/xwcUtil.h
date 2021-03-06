/* Copyright (c) 2015, Anton Lantcevich
    
   This file is part of the xwinclone.
   <https://github.com/awpe/xwinclone>
  
   Xwinclone is released under the BSD 3-Clause License.
   You should have received a copy of the BSD 3-Clause
   License along with this software; if not see
   <https://raw.githubusercontent.com/awpe/xwinclone/master/LICENSE.md>.  */

#ifndef XWCUTIL_H
#define	XWCUTIL_H

#include <defines.h>
#include <systemHeaders.h>
#include <xwcHeaders.h>

/****************************************/
/*Redefine imlib2 functions*/
/****************************************/
typedef
Imlib_Image (*imgLibCreateCrSc_t)(int, int, int, int, int, int) ;

extern imgLibCreateCrSc_t imgLibCreateCrSc;
/****************************************/

/** @var int LOG_LVL
@brief Sets logging level 0, 1, 2
 */
extern int LOG_LVL;

extern FILE * LOG_FILE;

/**
 * Processes log messages according to current logging level.
 * @param[in] msg Pointer to null-terminated C-string with message.
 * @param[in] lvl Desired log level of message
 * @param[in] sequenced if this log msg is a part of sequence
 */
void
logCtrl (const char * msg,
         int          lvl,
         Bool         sequenced);

/**
 * Prints out program version
 */
void
printVersion (void);

/**
 * Checks if no other instance of this program is running.
 */
Bool
checkInstCount (XWCContext * ctx);

Bool
bgImgPrepare (XWCContext * ctx,
              Pixmap     * bgImgPm,
              int        * bgImgWidth,
              int        * bgImgHeight);

void
printBlock (const char * text,
            const char * lnPreIn,
            const char * blPreIn,
            char       * extBuf,
            int          extBufLen);

Bool
createConfFile (XWCContext * ctx,
                arguments  * args);

Bool
getUserDir (XWCContext * ctx);

Bool
enableLogFile (XWCContext * ctx);

Bool
checkFileMode (const char * fname,
               int          mode);

void
printCurValues (arguments  * args);

void
printUsage (arguments  * args);

Bool
readConfFile (XWCContext * ctx,
              arguments  * args);

Bool
getArgName (arguments  * args,
            const char * buf,
            argNames   * retName);

Bool
mkdirRec (const char * dir);
#endif
