#include <xwcUtil.h>

Bool
createConfFile (XWCContext * ctx,
                arguments  * args)
{
    FILE * config;
    char buf[4096];
    char fnameTmp[1024];
    int  res;

    logCtrl ("Creating config file\n", LOG_LVL_1, False);

    if (ctx->confFileName == NULL)
    {
        logCtrl ("Error creating config file: config file name variable is "
                 "NULL!", LOG_LVL_NO, False);
        return False;
    }

    if (*ctx->confFileName == '~')
    {
        logCtrl ("\tgetting user directory", LOG_LVL_2, True);

        if (ctx->userDir == NULL)
        {
            logCtrl ("error: Cannot determine user home directory!",
                     LOG_LVL_NO, False);
            return False;
        }
        else
        {
            logCtrl ("\t\tsuccess", LOG_LVL_2, True);
        }

        snprintf (fnameTmp, sizeof (fnameTmp), "%s%s", ctx->userDir,
                  ctx->confFileName + 1);
    }
    else
    {
        snprintf (fnameTmp, sizeof (fnameTmp), "%s", ctx->confFileName);
    }

    if (checkFileMode (fnameTmp, W_OK) == False)
    {
        snprintf (buf, sizeof (buf), "No write permission for file %s",
                  fnameTmp);
        logCtrl (buf, LOG_LVL_NO, False);
        return False;
    }

    if ((config = fopen (fnameTmp, "w")) == NULL)
    {
        snprintf (buf, sizeof (buf), "Error opening file '%s' for writing "
                  "configuration!\nError: %s\n", fnameTmp,
                  strerror (errno));
        logCtrl (buf, LOG_LVL_NO, False);
        return False;
    }
    else
    {
        snprintf (buf, sizeof (buf), "\twill write config to %s\n", fnameTmp);
        logCtrl (buf, LOG_LVL_1, False);
    }

    for (int i = 0; i < args->m_ArgCnt; ++ i)
    {
        if (args->m_Args[i]->m_HasValue)
        {
            printBlock (args->m_Args[i]->m_Comment, "# ", NULL, buf,
                        sizeof (buf));
            res = fprintf (config, "%s#\n", buf);
            if (args->m_Args[i]->m_Type == C_STR)
            {
                res = fprintf (config, "%s = \"%s\"\n\n", args->m_Args[i]->m_NameStr,
                               (const char *) args->m_Args[i]->m_Value );
            }
            else if (args->m_Args[i]->m_Type == INT)
            {
                res = fprintf (config, "%s = %d\n\n", args->m_Args[i]->m_NameStr,
                               *( (int *) args->m_Args[i]->m_Value) );
            }

            if (res < 0)
            {
                snprintf (buf, sizeof (buf), "Error writing arument %s to "
                          "config file\n", args->m_Args[i]->m_NameStr);
                logCtrl (buf, LOG_LVL_NO, False);
                return False;
            }
        }
    }

    fclose (config);

    return True;
}