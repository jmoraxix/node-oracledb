/* Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved. */

/******************************************************************************
 *
 * You may not use the identified files except in compliance with the Apache 
 * License, Version 2.0 (the "License.")
 *
 * You may obtain a copy of the License at 
 * http://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * NAME
 *   dpiUtils.cpp - ConnImpl class implementation 
 *
 * DESCRIPTION
 *
 *****************************************************************************/

#include <stdio.h>
#include <string.h>

#ifndef DPIUTILS_ORACLE
# include <dpiUtils.h>
#endif


#ifndef DPIEXCEPTIONIMPL_ORACLE
# include <dpiExceptionImpl.h>
#endif

#ifdef WIN32
  #define  snprintf  _snprintf
#endif



/*---------------------------------------------------------------------------
                     PUBLIC FUNCTIONS
  ---------------------------------------------------------------------------*/


/*****************************************************************************/
/*
   DESCRIPTION
     This routine retrives the error information from the OCI error handle and
     throws ExceptionImpl with the information contained in the error handle.

   PARAMETERS:
     rc   - OCI return code
     errh - OCI error hanlde

   RETURNS:
     nothing

   NOTES:
 */

void ociCall(sword rc, OCIError *errh)
{
  if (!rc)
    return;
  
  OraText ociErrorMsg[OCI_ERROR_MAXMSG_SIZE];
  sb4     ociErrorNo = 0;
  memset(ociErrorMsg, 0, OCI_ERROR_MAXMSG_SIZE);
  
  rc = OCIErrorGet(errh, 1, NULL, &ociErrorNo, ociErrorMsg,
                   OCI_ERROR_MAXMSG_SIZE-1, OCI_HTYPE_ERROR);
  if (rc)
    throw ExceptionImpl(DpiErrUnkOciError);
  else
  {
    ociErrorMsg[strlen((char*)ociErrorMsg)-1]=0; //strip off newline
    throw ExceptionImpl("ORA", ociErrorNo, (const char *)ociErrorMsg);
  }
}



/*****************************************************************************/
/*
   DESCRIPTION
     This routine retrives the error information from the OCI environment
     handle and throws ExceptionImpl with the information contained in the
     error handle.

   PARAMETERS:
     rc   - OCI return code
     envh - OCI environment hanlde

   RETURNS:
     nothing

   NOTES:
     
 */

void ociCallEnv(sword rc, OCIEnv *envh)
{
  if (!rc)
    return;
  
  OraText ociErrorMsg[OCI_ERROR_MAXMSG_SIZE];
  sb4     ociErrorNo = 0;
  memset(ociErrorMsg, 0, OCI_ERROR_MAXMSG_SIZE);
  
  rc = OCIErrorGet(envh, 1, NULL, &ociErrorNo, ociErrorMsg,
                   OCI_ERROR_MAXMSG_SIZE-1, OCI_HTYPE_ENV);
  if (rc)
    throw ExceptionImpl(DpiErrUnkOciError);
  else
  {
    ociErrorMsg[strlen((char*)ociErrorMsg)-1]=0; //strip off newline
    throw ExceptionImpl("ORA", ociErrorNo, (const char *)ociErrorMsg);
  }
}




/* end of file dpiUtils.cpp */

