/* Copyright (c) 2015, Anton Lantcevich
    
   This file is part of the xwinclone.
   <https://github.com/awpe/xwinclone>
  
   Xwinclone is released under the BSD 3-Clause License.
   You should have received a copy of the BSD 3-Clause
   License along with this software; if not see
   <https://raw.githubusercontent.com/awpe/xwinclone/master/LICENSE.md>.  */

#include <xwcDevCtrl.h>

void
ungrabAllKeys (XWCContext * ctx)
{
    if (ctx->devsAcquired)
    {
        grabKeyCtrl (ctx, ctx->rootW, ctx->exitKeyCode, ctx->nMods,
                     ctx->exitMods, False);
        grabKeyCtrl (ctx, ctx->rootW, ctx->cloneKeyCode, ctx->nMods,
                     ctx->clMods, False);
    }
}
