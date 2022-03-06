# NoteManSlide ポートフォリオ
### 概要
このプログラムは自作リズムゲームの譜面をGUIベースで作成できるものです。テストプレイ機能もあります。  
肝心の本体はまだ未開発ですので、現状の用途は自分で好きな譜面を作ってそれをテストプレイ機能で遊ぶことになります。  
出力する譜面データはJSONファイルです。テストプレイでは実際に出力されるJSONデータから譜面を作っています。  
対応するノーツは3種類で、普通のノーツとロングノーツとスライドノーツです。
レーン数は6レーンとなっています。  

<p>
 <img src="https://github.com/yanshi-che/imageContainer/blob/main/%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB1.PNG" width=400px height=400px />
<img src="https://github.com/yanshi-che/imageContainer/blob/main/%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB2.PNG" width=400px height=400px />
</p>
  
### ポイント
ポイントは何といっても譜面が視覚的に簡単に作れるところです。リズムゲームに曲と譜面は必要不可欠です。中にはCSVファイルに手書きで書いているケースもあったりしますが、それだと時間がかかりますし、何より見た目が分かりにくいです。これを作ったことで譜面の供給効率が劇的に改善します。
  
### 起動用exeファイルのURL
https://drive.google.com/file/d/1v0bAv89_j6ZZxMdS-jsfZfoZTpFmayzi/view?usp=sharing
  
### 簡易的なファイル間の関係
<p>
 <img src="https://github.com/yanshi-che/imageContainer/blob/main/noteSlide.png" width=400px height=400px />
</p>
  
### 使用技術・ライブラリ
- C++
- boosC++ version 1.77
- winAPI
- Dxlib windows版 ForVisualStudio version 3.22
  
### 今後の改善点
- BPMが途中で変化する曲には対応していないためその対応
- 4/4拍子を前提としているため、それ以外の拍子の対応
- 使用しているJSONパースでは日本語が対応していないためその対応
- 直前の操作のやり直し機能の追加
- テストプレイ機能での、曲の巻き戻し機能など
  
### 使用しているライブラリのライセンス表記
- Boost Library Licence
  
Boost Software License - Version 1.0 - August 17th, 2003  
  
Permission is hereby granted, free of charge, to any person or organization  
obtaining a copy of the software and accompanying documentation covered by  
this license (the "Software") to use, reproduce, display, distribute,  
execute, and transmit the Software, and to prepare derivative works of the  
Software, and to permit third-parties to whom the Software is furnished to  
do so, all subject to the following:  
  
The copyright notices in the Software and this entire statement, including  
the above license grant, this restriction and the following disclaimer,  
must be included in all copies of the Software, in whole or in part, and  
all derivative works of the Software, unless such copies or derivative  
works are solely in the form of machine-executable object code generated by  
a source language processor.  

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,  
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT  
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE  
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,  
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER  
DEALINGS IN THE SOFTWARE.  


- Dxlib著作権表記  

libjpeg　Copyright (C) 1991-2013, Thomas G. Lane, Guido Vollbeding.  
　　　this software is based in part on the work of the Independent JPEG Group  


　　　libpng　Copyright (C) 2004, 2006-2012 Glenn Randers-Pehrson.  
　　　zlib　Copyright (C) 1995-2012 Jean-loup Gailly and Mark Adler.  


　　　libtiff　Copyright (c) 1988-1997 Sam Leffler  
　　　libtiff　Copyright (c) 1991-1997 Silicon Graphics, Inc.  

　　　Permission to use, copy, modify, distribute, and sell this software and  
　　　its documentation for any purpose is hereby granted without fee, provided  
　　　that (i) the above copyright notices and this permission notice appear in  
　　　all copies of the software and related documentation, and (ii) the names of  
　　　Sam Leffler and Silicon Graphics may not be used in any advertising or  
　　　publicity relating to the software without the specific, prior written  
　　　permission of Sam Leffler and Silicon Graphics.  

　　　THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,  
　　　EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY  
　　　WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  

　　　IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR  
　　　ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,  
　　　OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,  
　　　WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF  
　　　LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE  
　　　OF THIS SOFTWARE.  


　　　libogg　Copyright (C) 2002-2009 Xiph.org Foundation  

　　　Redistribution and use in source and binary forms, with or without  
　　　modification, are permitted provided that the following conditions  
　　　are met:  

　　　- Redistributions of source code must retain the above copyright  
　　　notice, this list of conditions and the following disclaimer.  

　　　- Redistributions in binary form must reproduce the above copyright  
　　　notice, this list of conditions and the following disclaimer in the  
　　　documentation and/or other materials provided with the distribution.  

　　　- Neither the name of the Xiph.org Foundation nor the names of its  
　　　contributors may be used to endorse or promote products derived from  
　　　this software without specific prior written permission.  

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS  
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT  
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION  
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  
　　　SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT  
　　　LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  
　　　OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  


　　　Opus audio codec  
　　　Copyright 2001-2011 Xiph.Org, Skype Limited, Octasic,  
　　　 Jean-Marc Valin, Timothy B. Terriberry,  
　　　 CSIRO, Gregory Maxwell, Mark Borgerding,  
　　　 Erik de Castro Lopo  

　　　Redistribution and use in source and binary forms, with or without  
　　　modification, are permitted provided that the following conditions  
　　　are met:  

　　　- Redistributions of source code must retain the above copyright  
　　　notice, this list of conditions and the following disclaimer.  

　　　- Redistributions in binary form must reproduce the above copyright  
　　　notice, this list of conditions and the following disclaimer in the  
　　　documentation and/or other materials provided with the distribution.  

　　　- Neither the name of Internet Society, IETF or IETF Trust, nor the  
　　　names of specific contributors, may be used to endorse or promote  
　　　products derived from this software without specific prior written  
　　　permission.  

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS  
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT  
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER  
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,  
　　　EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,  
　　　PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR  
　　　PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF  
　　　LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING  
　　　NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS  
　　　SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  


　　　Opusfile  
　　　Copyright (c) 1994-2013 Xiph.Org Foundation and contributors  

　　　Redistribution and use in source and binary forms, with or without  
　　　modification, are permitted provided that the following conditions  
　　　are met:  

　　　- Redistributions of source code must retain the above copyright  
　　　notice, this list of conditions and the following disclaimer.  

　　　- Redistributions in binary form must reproduce the above copyright  
　　　notice, this list of conditions and the following disclaimer in the  
　　　documentation and/or other materials provided with the distribution.  

　　　- Neither the name of the Xiph.Org Foundation nor the names of its  
　　　contributors may be used to endorse or promote products derived from  
　　　this software without specific prior written permission.  

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS  
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT  
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION  
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  
　　　SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT  
　　　LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  
　　　OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  


　　　Mersenne Twister  
　　　Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,  
　　　All rights reserved.  

　　　Redistribution and use in source and binary forms, with or without  
　　　modification, are permitted provided that the following conditions  
　　　are met:  

　　　1. Redistributions of source code must retain the above copyright  
　　　notice, this list of conditions and the following disclaimer.  

　　　2. Redistributions in binary form must reproduce the above copyright  
　　　notice, this list of conditions and the following disclaimer in the  
　　　documentation and/or other materials provided with the distribution.  

　　　3. The name of the author may not be used to endorse or promote products  
　　　derived from this software without specific prior written permission.  

　　　THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  
　　　IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  
　　　OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
　　　IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,  
　　　INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  
　　　NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  
　　　THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  


　　　Bullet　Copyright (c) 2003-2006 Erwin Coumans.  
