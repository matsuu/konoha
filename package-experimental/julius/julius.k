/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2008, Masaaki Goshima <goccy@users.sourceforge.jp>
 *           (c) 2008-      Konoha Software Foundation
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * See www.konohaware.org/license.html for further information.
 *
 * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
 * (2) Konoha Software Foundation License 1.0
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Class Definition */

class Julius;
class Recog;
class Jconf;
class WordInfo;
class RecogProcess;
class Sentence;

/*--------------------------------------------------------------------------*/
/*Recog*/

Recog Recog.new(Jconf jconf);
void Recog.callbackAddFuncRecReady(int code,Closure c,String data);
void Recog.callbackAddFuncRecStart(int code,Closure c,String data);
void Recog.callbackAddFuncOutputResult(int code,Closure c,String data);
void Recog.recogInfo();
void Recog.recogFree();
int Recog.speechInput();
Boolean Recog.adinInit();
int Recog.openStream(String file_or_dev_name);
int Recog.recognizeStream();
void Recog.closeStream();
Boolean Recog.callbackExist(int code);
Boolean Recog.callbackDelete(int id);
void Recog.requestPause();
void Recog.requestTerminate();
void Recog.requestResume();
Boolean Recog.processDeactivateById(int id);
Boolean Recog.processActivate(String name);

/*-------------------------------------------------------------------------*/
/*Jconf*/

Jconf Jconf.new();
void Jconf.openInputStream(Recog recog);

/*-------------------------------------------------------------------------*/
/*Julius*/

void Julius.strmatch();
int Julius.fflush();
String Julius.getCurrentFilename();
void Julius.outputArgumentHelp();
void Julius.putVersion(FILE strm);
String Julius.getLineFromStdin(String buf,int buflen,String prompt);

/*-------------------------------------------------------------------------*/
/*WordInfo*/

WordInfo WordInfo.new(RecogProcess r);
int WordInfo.getWlen(int w);
String WordInfo.centerName(int j,int w);
void WordInfo.outputAlignment(int n,RecogProcess r);

/*-------------------------------------------------------------------------*/
/*Sentence*/

Sentence Sentence.new(RecogProcess r,int n,WordInfo winfo);
int Sentence.getSeq(int i);
int Sentence.getWordNum();

/*-------------------------------------------------------------------------*/
/*RecogProcess*/

RecogProcess RecogProcess.new(Recog recog);
Boolean RecogProcess.getNext();
int RecogProcess.checkLive();
int RecogProcess.checkResultStatus();
int RecogProcess.sentNum();
void RecogProcess.outputWordScore(int n);




