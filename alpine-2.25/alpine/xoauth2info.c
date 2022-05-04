/*
 * ========================================================================
 * Copyright 2013-2021 Eduardo Chappa
 * Copyright 2006-2009 University of Washington
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * ========================================================================
 */
#include "../alpine/xoauth2.h"

XOAUTH2_INFO_S xoauth_default[] = {
  { GMAIL_NAME, GMAIL_ID, GMAIL_SECRET, GMAIL_TENANT, NULL, NULL},
  { OUTLOOK_NAME, OUTLOOK_ID, OUTLOOK_SECRET, OUTLOOK_TENANT, NULL, NULL},
  { YAHOO_NAME, YAHOO_ID, YAHOO_SECRET, YAHOO_TENANT, NULL, NULL},
  { YANDEX_NAME, YANDEX_ID, YANDEX_SECRET, YANDEX_TENANT, NULL, NULL},
  { NULL, NULL, NULL, NULL, NULL, NULL}
};

/*
 * This is the private information of the client, which is passed to
 * c-client for processing. Every c-client application must have its
 * own.
 */
OAUTH2_S alpine_oauth2_list[] = {
  {GMAIL_NAME,
   {"imap.gmail.com", "smtp.gmail.com", NULL, NULL},
   {{"client_id", NULL},
    {"client_secret", NULL},
    {"tenant", NULL},		/* not used */
    {"code", NULL},		/* access code from the authorization process */
    {"refresh_token", NULL},
    {"scope", "https://mail.google.com/"},
    {"redirect_uri", "urn:ietf:wg:oauth:2.0:oob"},
    {"grant_type", "authorization_code"},
    {"grant_type", "refresh_token"},
    {"response_type", "code"},
    {"state", NULL},
    {"device_code", NULL}	/* not used */
   },
   {{"GET", (unsigned char *) "https://accounts.google.com/o/oauth2/auth",	/* authorization address, get access code */
	{OA2_Id, OA2_Scope, OA2_Redirect, OA2_Response, OA2_End, OA2_End, OA2_End}},
    {NULL, NULL, {OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End}},	/* Device Info information, not used */
    {"POST", (unsigned char *) "https://accounts.google.com/o/oauth2/token",	/* Address to get refresh token from access code */
	{OA2_Id, OA2_Secret, OA2_Redirect, OA2_GrantTypeforAccessToken, OA2_Code, OA2_End, OA2_End}},
    {"POST", (unsigned char *) "https://accounts.google.com/o/oauth2/token",	/* access token from refresh token */
	{OA2_Id, OA2_Secret, OA2_RefreshToken, OA2_GrantTypefromRefreshToken, OA2_End, OA2_End, OA2_End}}
   },
   {NULL, NULL, NULL, 0, 0, NULL},	/* device_code information */
    NULL, 	/* access token */
    NULL,	/* special IMAP ID */
    0,		/* do not hide */
    0, 		/* expiration time */
    0, 		/* first time indicator */
    1,		/* client secret required */
    0,		/* Cancel refresh token */
    GMAIL_FLAGS	/* default flags. For Gmail this should be set to OA2_AUTHORIZE */
  },
  {OUTLOOK_NAME,
   {"outlook.office365.com", "smtp.office365.com", NULL, NULL},
   {{"client_id", NULL},
    {"client_secret", NULL},		/* not used, but needed */
    {"tenant", NULL},			/* used */
    {"code", NULL},			/* not used, not needed */
    {"refresh_token", NULL},
    {"scope", "offline_access https://outlook.office.com/IMAP.AccessAsUser.All https://outlook.office.com/SMTP.Send"},
    {"grant_type", "urn:ietf:params:oauth:grant-type:device_code"},
    {"scope", NULL},			/* not used */
    {"grant_type", "refresh_token"},
    {"response_type", "code"},		/* not used */
    {"state", NULL},			/* not used */
    {"device_code", NULL}		/* only used for frst time set up */
   },
   {{NULL, NULL, {OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End}}, /* Get Access Code, Not used */
    {"POST", (unsigned char *) "https://login.microsoftonline.com/\001/oauth2/v2.0/devicecode",	/* first time use and get device code information */
	{OA2_Id, OA2_Scope, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End}},
    {"POST", (unsigned char *) "https://login.microsoftonline.com/\001/oauth2/v2.0/token",	/* Get first Refresh Token and Access token  */
	{OA2_Id, OA2_Redirect, OA2_DeviceCode, OA2_End, OA2_End, OA2_End, OA2_End}},
    {"POST", (unsigned char *) "https://login.microsoftonline.com/\001/oauth2/v2.0/token",	/* Get access token from refresh token */
	{OA2_Id, OA2_RefreshToken, OA2_Scope, OA2_GrantTypefromRefreshToken, OA2_End, OA2_End, OA2_End}}
   },
   {NULL, NULL, NULL, 0, 0, NULL},	/* device_code information */
    NULL, 	/* access token */
    NULL,	/* special IMAP ID */
    0,		/* do not hide */
    0, 		/* expiration time */
    0, 		/* first time indicator */
    0,		/* client secret required */
    0,		/* Cancel refresh token */
    OUTLOOK_FLAGS /* default flags. For OUTLOOK this should be set to OA2_DEVICE */
  },
  {OUTLOOK_NAME,
   {"outlook.office365.com", "smtp.office365.com", NULL, NULL},
   {{"client_id", NULL},
    {"client_secret", NULL},		/* not used, but needed */
    {"tenant", NULL},			/* used */
    {"code", NULL},			/* used during authorization */
    {"refresh_token", NULL},
    {"scope", "offline_access https://outlook.office.com/IMAP.AccessAsUser.All https://outlook.office.com/SMTP.Send"},
    {"redirect_uri", "http://localhost"},
    {"grant_type", "authorization_code"},
    {"grant_type", "refresh_token"},
    {"response_type", "code"},
    {"state", NULL},			/* not used */
    {"device_code", NULL}		/* not used */
   },
   {{"GET", (unsigned char *) "https://login.microsoftonline.com/\001/oauth2/v2.0/authorize",	/* Get Access Code */
	{OA2_Id, OA2_Scope, OA2_Redirect, OA2_Response, OA2_End, OA2_End, OA2_End}},
    {NULL, NULL, {OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End}}, /* device code, not used */
    {"POST", (unsigned char *) "https://login.microsoftonline.com/\001/oauth2/v2.0/token",	/* Get first Refresh Token and Access token  */
	{OA2_Id, OA2_Redirect, OA2_Scope, OA2_GrantTypeforAccessToken, OA2_Secret, OA2_Code, OA2_End}},
    {"POST", (unsigned char *) "https://login.microsoftonline.com/\001/oauth2/v2.0/token",	/* Get access token from refresh token */
	{OA2_Id, OA2_RefreshToken, OA2_Scope, OA2_GrantTypefromRefreshToken, OA2_Secret, OA2_End, OA2_End}}
   },
   {NULL, NULL, NULL, 0, 0, NULL},	/* device_code information, not used */
    NULL, 	/* access token */
    NULL,	/* special IMAP ID */
    0,		/* do not hide */
    0, 		/* expiration time */
    0, 		/* first time indicator */
    1,		/* client secret required */
    0,		/* Cancel refresh token */
    OUTLOOK_FLAGS /* default flags. For OUTLOOK this should be set to OA2_DEVICE */
  },
  {YAHOO_NAME,
   {"imap.mail.yahoo.com", "smtp.mail.yahoo.com", NULL, NULL},
   {{"client_id", NULL},
    {"client_secret", NULL},		/* used */
    {"tenant", NULL},			/* not used */
    {"code", NULL},			/* used during authorization */
    {"refresh_token", NULL},
    {"scope", NULL},			/* not used! */
    {"redirect_uri", "oob"},		/* https://localhost */
    {"grant_type", "authorization_code"},
    {"grant_type", "refresh_token"},
    {"response_type", "code"},
    {"state", NULL},			/* used */
    {"device_code", NULL}		/* not used */
   },
   {{"GET", (unsigned char *) "https://api.login.yahoo.com/oauth2/request_auth",	/* Get Access Code */
	{OA2_Id, OA2_Redirect, OA2_Response, OA2_State, OA2_End, OA2_End, OA2_End}},
    {NULL, NULL, {OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End}}, /* device code, not used */
    {"POST", (unsigned char *) "https://api.login.yahoo.com/oauth2/get_token",	/* Get first Refresh Token and Access token  */
	{OA2_Id, OA2_Secret, OA2_Redirect, OA2_Code, OA2_GrantTypeforAccessToken, OA2_End, OA2_End}},
    {"POST", (unsigned char *) "https://api.login.yahoo.com/oauth2/get_token",	/* Get access token from refresh token */
	{OA2_Id, OA2_Secret, OA2_Redirect, OA2_RefreshToken, OA2_GrantTypefromRefreshToken, OA2_End, OA2_End}}
   },
   {NULL, NULL, NULL, 0, 0, NULL},	/* device_code information, not used */
    NULL, 	/* access token */
    "ALPINE_V1",	/* special IMAP ID */
    1,		/* hide */
    0, 		/* expiration time */
    0, 		/* first time indicator */
    1,		/* client secret required */
    0,		/* Cancel refresh token */
    YAHOO_FLAGS	/* default flags. For YAHOO this should be set to OA2_AUTHORIZE */
  },
  {YANDEX_NAME,
   {"imap.yandex.com", "smtp.yandex.com", NULL, NULL},
   {{"client_id", NULL},
    {"client_secret", NULL},		/* not used, but needed */
    {"tenant", NULL},			/* not used */
    {"code", NULL},			/* used during authorization */
    {"refresh_token", NULL},
    {"scope", NULL},			/* not needed, so not used */
    {"redirect_uri", "https://oauth.yandex.ru/verification_code"},
    {"grant_type", "authorization_code"},
    {"grant_type", "refresh_token"},
    {"response_type", "code"},
    {"state", NULL},			/* not used */
    {"device_code", NULL}		/* not used */
   },
   {{"GET", (unsigned char *) "https://oauth.yandex.com/authorize",	/* Get Access Code */
	{OA2_Id, OA2_Redirect, OA2_Response, OA2_End, OA2_End, OA2_End, OA2_End}},
    {NULL, NULL, {OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End, OA2_End}}, /* device code, not used */
    {"POST", (unsigned char *) "https://oauth.yandex.com/token",	/* Get first Refresh Token and Access token  */
	{OA2_Id, OA2_Redirect, OA2_GrantTypeforAccessToken, OA2_Secret, OA2_Code, OA2_End, OA2_End}},
    {"POST", (unsigned char *) "https://oauth.yandex.com/token",	/* Get access token from refresh token */
	{OA2_Id, OA2_RefreshToken, OA2_GrantTypefromRefreshToken, OA2_Secret, OA2_End, OA2_End, OA2_End}}
   },
   {NULL, NULL, NULL, 0, 0, NULL},	/* device_code information, not used */
    NULL, 	/* access token */
    NULL,	/* special IMAP ID */
    0,		/* do not hide */
    0, 		/* expiration time */
    0, 		/* first time indicator */
    1,		/* client secret required */
    0,		/* Cancel refresh token */
    YANDEX_FLAGS /* default flags. For YANDEX this should be set to OA2_AUTHORIZE */
  },
  {NULL, 	/* Name, unsigned char * */
   {NULL, NULL, NULL, NULL }, /* host and equivalents */
   {{NULL, NULL},  /* client-id */
    {NULL, NULL},  /* client-secret */
    {NULL, NULL},  /* tenant - outlook */
    {NULL, NULL},  /* access_code, for authorize method */
    {NULL, NULL},  /* refresh token */
    {NULL, NULL},  /* scope  */
    {NULL, NULL},  /* redirect */
    {NULL, NULL},  /* grant type for access token */
    {NULL, NULL},  /* grant type from refresh token */
    {NULL, NULL},  /* response */
    {NULL, NULL},  /* state */
    {NULL, NULL}   /* device code */
   },
   {{NULL, NULL, {0, 0, 0, 0, 0, 0, 0}}, /* method, server, parameters for authorize */
    {NULL, NULL, {0, 0, 0, 0, 0, 0, 0}}, /* method, server, parameters for device login */
    {NULL, NULL, {0, 0, 0, 0, 0, 0, 0}}, /* method, server, parameters for getting refresh token */
    {NULL, NULL, {0, 0, 0, 0, 0, 0, 0}}  /* method, server, parameters for refreshing access token */
   },
   {NULL, NULL, NULL, 0, 0, NULL},	/* device_code information */
   NULL,				/* access token */
   NULL,				/* special IMAP ID */
   0,					/* Hide this */
   0,					/* expiration time */
   0,					/* first time */
   0,					/* require secret */
   0,					/* cancel refresh token */
   0					/* flags */
  }
};
