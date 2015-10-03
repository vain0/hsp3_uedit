;
;	HSP help manager用 HELPソースファイル
;	(先頭が「;」の行はコメントとして処理されます)
;

%type
HSPシステム変数
%ver
3.2
%note
ver3.2標準
%date
2009/05/15
%author
onitama
%url
http://www.onionsoft.net/
%port
Win
Cli
Let


;---------------------------------------------------------------------
%index
hspstat
HSPランタイムの情報を取得する

%group
システム変数

%inst
HSPランタイムの情報が整数値で代入されます。以下の情報がすべて合計された値になります。
 デバッグモード = 1
 スクリーンセーバー起動時 = 2
 コンソールモード = 16
 Macintosh版HSP = $80
 Linux版HSP = $1000

%href
_debug

;---------------------------------------------------------------------
%index
hspver
HSPのバージョン番号

%group
システム変数

%inst
HSP のバージョン番号が整数値で代入されます。バージョンコード +  マイナーバージョンコードの値になります。(3.0 は $3??? になる)

%href
__hspver__

;---------------------------------------------------------------------
%index
cnt
ループのカウンター

%group
システム変数

%inst
repeat〜loopループのカウンターが整数値で代入されます。

%href
repeat
foreach
loop

;---------------------------------------------------------------------
%index
err
HSPのエラーコード

%group
システム変数

%inst
HSPのエラーコードです。エラーコードとメッセージの対応については、別途マニュアル(error.htm)を参照してください。


%href
onerror


;---------------------------------------------------------------------
%index
stat
色々な命令のステータス値

%group
システム変数

%inst
色々な命令を実行した結果(ステータス)が整数値で代入されます。

%href
return
dialog
mref

;---------------------------------------------------------------------
%index
mousex
マウスカーソルのX座標

%group
システム変数

%inst
マウスカーソルのX座標が整数値で代入されます。

%sample
	; マウスポインタの動きに沿って線を描く
	repeat
		line mousex, mousey
		wait 1
		loop
%href
mouse
mousey
mousew
ginfo_mx

;---------------------------------------------------------------------
%index
mousey
マウスカーソルのY座標

%group
システム変数

%inst
マウスカーソルのY座標が整数値で代入されます。

%sample
	; マウスポインタの動きに沿って線を描く
	repeat
		line mousex, mousey
		wait 1
		loop

%href
mouse
mousex
mousew
ginfo_my

;---------------------------------------------------------------------
%index
mousew
マウスカーソルのホイール値

%group
システム変数

%inst
ホイール付きマウスの移動量が整数値で代入されます。

%href
mousex
mousey
%port-
Let

;---------------------------------------------------------------------
%index
strsize
読み出しバイト数

%group
システム変数

%inst
getstr、exist、bload命令などで読み出したバイト数が代入されます。

%href
bload
exist
getstr

;---------------------------------------------------------------------
%index
refstr
色々な命令のステータス文字列


%group
システム変数

%inst
色々な命令を実行した結果の文字列が代入されます。

%href
return
dialog
mref

;---------------------------------------------------------------------
%index
looplev
repeatのネストレベル

%group
システム変数

%inst
repeat〜loopのネストレベルが代入されます。

%href
repeat
foreach
loop

;---------------------------------------------------------------------
%index
sublev
サブルーチンのネストレベル

%group
システム変数

%inst
サブルーチン(またはユーザー定義命令、関数) のネストレベルが代入されます。

%href
gosub
return

;---------------------------------------------------------------------
%index
iparam
割り込み要因を示す値

%group
システム変数

%inst
割り込み要因を示す値が代入されます。
oncmd命令による割り込み時は、割り込みメッセージのIDが代入されます。
onexit命令による終了割り込み時は、通常のウィンドウクローズによる終了であれば0が、シャットダウン等のシステム通知による終了であれば1が代入されます。


%href
onkey
onclick
onexit
lparam
wparam
onerror
oncmd

%sample
	onkey goto *lab
	stop
*lab
	mes "キーコード : "+wparam+", 文字コード : "+iparam
	stop
%port-
Let

;---------------------------------------------------------------------
%index
wparam
割り込み時のwParam

%group
システム変数

%inst
割り込み時に保存される Windows のシステム値 (wParam) が代入されます。

%href
onkey
onclick
onerror
iparam
lparam
onerror
oncmd

%sample
	onkey goto *lab
	stop
*lab
	a = lparam>>24&1
	mes "キーコード : "+wparam+", 拡張キーフラグ : "+a
	stop
%port-
Let

;---------------------------------------------------------------------
%index
lparam
割り込み時のlParam

%group
システム変数

%inst
割り込み時に保存される Windows のシステム値 (lParam) が代入されます。

%href
onkey
onclick
onerror
iparam
wparam
onerror
oncmd

%sample
	onkey goto *lab
	stop
*lab
	a = lparam>>24&1
	mes "キーコード : "+wparam+", 拡張キーフラグ : "+a
	stop
%port-
Let

;---------------------------------------------------------------------
%index
hwnd
現在のウィンドウハンドル

%group
システム変数

%inst
現在選択されているウィンドウのハンドル(ポインタ)が代入されます。
主にDLL等の外部呼出しで必要な場合に参照されます。

%href
mref

;---------------------------------------------------------------------
%index
hdc
現在のデバイスコンテキスト

%group
システム変数

%inst
現在選択されているウィンドウのデバイスコンテキスト(ポインタ)が代入されます。
主にDLL等の外部呼出しで必要な場合に参照されます。

%href
mref

;---------------------------------------------------------------------
%index
hinstance
現在のインスタンスハンドル

%group
システム変数

%inst
現在実行中アプリケーションのインスタンスハンドル(ポインタ)が代入されます。
主にDLL等の外部呼出しで必要な場合に参照されます。

%href
mref
%port-
Let

;---------------------------------------------------------------------
%index
refdval
色々な命令のステータス実数値

%group
システム変数

%inst
色々な命令を実行した結果の実数値が代入されます。

%href
return

;---------------------------------------------------------------------
%index
thismod
現在の有効なモジュール変数

%group
システム変数

%inst
モジュール変数処理のためのユーザー定義命令・関数内で、
渡されたモジュール変数自身を示す名称として使用することができます。
#modfuncで定義されたルーチンから、別な命令・関数を呼び出す場合に使用することができます。

%href
newmod
delmod
%port-
Let

;---------------------------------------------------------------------
%index
notemax
メモリノートパッドの行数

%group
システム変数

%inst
現在選択されているメモリノートパッド全体の行数を示すシステム変数として使用することができます。
noteinfo関数でも同様の情報を取得することが可能です。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
noteinfo

;---------------------------------------------------------------------
%index
notesize
メモリノートパッドの文字数

%group
システム変数

%inst
現在選択されているメモリノートパッド全体の文字数(byte数)を示す
システム変数として使用することができます。
noteinfo関数でも同様の情報を取得することが可能です。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
noteinfo

;---------------------------------------------------------------------
%index
ginfo_mx
スクリーン上のマウスカーソルX座標

%group
システム変数

%inst
スクリーン上のマウスカーソルX座標が代入されています。
スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、デスクトップ画面全体から見た座標になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo
ginfo_my

;---------------------------------------------------------------------
%index
ginfo_my
スクリーン上のマウスカーソルY座標

%group
システム変数

%inst
スクリーン上のマウスカーソルY座標が代入されています。
スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、デスクトップ画面全体から見た座標になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo
ginfo_mx

;---------------------------------------------------------------------
%index
ginfo_act
アクティブなウィンドウID

%group
システム変数

%inst
現在アクティブになっているウィンドウIDが代入されています。
もし、 アクティブになっているウィンドウがHSP以外の場合は-1になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo

;---------------------------------------------------------------------
%index
ginfo_sel
操作先ウィンドウID

%group
システム変数

%inst
gsel命令で指定した画面の操作先ウィンドウIDが代入されています。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
gsel
ginfo

;---------------------------------------------------------------------
%index
ginfo_wx1
ウィンドウの左上X座標

%group
システム変数

%inst
スクリーン座標系で現在のウィンドウの左上X座標が代入されています。
スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、デスクトップ画面全体から見た座標になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_wy1
ginfo_wx2
ginfo_wy2
ginfo

;---------------------------------------------------------------------
%index
ginfo_wy1
ウィンドウの左上Y座標

%group
システム変数

%inst
スクリーン座標系で現在のウィンドウの左上Y座標が代入されています。
スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、デスクトップ画面全体から見た座標になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_wx1
ginfo_wx2
ginfo_wy2
ginfo

;---------------------------------------------------------------------
%index
ginfo_wx2
ウィンドウの右下X座標

%group
システム変数

%inst
スクリーン座標系で現在のウィンドウの右下X座標が代入されています。
スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、デスクトップ画面全体から見た座標になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_wy2
ginfo_wx1
ginfo_wy1
ginfo

;---------------------------------------------------------------------
%index
ginfo_wy2
ウィンドウの右下Y座標

%group
システム変数

%inst
スクリーン座標系で現在のウィンドウの右下Y座標が代入されています。
スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、デスクトップ画面全体から見た座標になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_wx2
ginfo_wx1
ginfo_wy1
ginfo

;---------------------------------------------------------------------
%index
ginfo_vx
ウィンドウのスクロールX座標

%group
システム変数

%inst
現在の操作先ウィンドウのスクロールX座標が代入されています。
これは、初期化サイズよりもウィンドウサイズが小さくなっている場合に、左上に表示されている座標がどれだけスクロールされているかを示す値です。
スクロールさせていない通常の状態では、(0,0)になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_vy
ginfo

;---------------------------------------------------------------------
%index
ginfo_vy
ウィンドウのスクロールY座標

%group
システム変数

%inst
現在の操作先ウィンドウのスクロールY座標が代入されています。
これは、初期化サイズよりもウィンドウサイズが小さくなっている場合に、左上に表示されている座標がどれだけスクロールされているかを示す値です。
スクロールさせていない通常の状態では、(0,0)になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_vx
ginfo

;---------------------------------------------------------------------
%index
ginfo_sizex
ウィンドウ全体のXサイズ

%group
システム変数

%inst
現在の操作先ウィンドウの横幅が代入されています。
これは、ウィンドウの枠やタイトルバーなども含めたサイズになります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_sizey
ginfo

;---------------------------------------------------------------------
%index
ginfo_sizey
ウィンドウ全体のYサイズ

%group
システム変数

%inst
現在の操作先ウィンドウの縦幅が代入されています。
これは、ウィンドウの枠やタイトルバーなども含めたサイズになります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_sizex
ginfo

;---------------------------------------------------------------------
%index
ginfo_winx
画面の描画エリアXサイズ

%group
システム変数

%inst
現在のウィンドウ描画エリアの横幅サイズが代入されています。
(buffer命令で作成された画面の場合は、初期化された画面サイズになります。)
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_sy
ginfo

;---------------------------------------------------------------------
%index
ginfo_winy
画面の描画エリアYサイズ

%group
システム変数

%inst
現在のウィンドウ描画エリアの縦幅サイズが代入されています。
(buffer命令で作成された画面の場合は、初期化された画面サイズになります。)
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_sx
ginfo

;---------------------------------------------------------------------
%index
ginfo_sx
画面の初期化Xサイズ

%group
システム変数

%inst
現在の操作先ウィンドウの初期化Xサイズが代入されています。
(最初にscreen,bgscr,buffer命令で初期化された画面サイズになります。)
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_winy
ginfo

;---------------------------------------------------------------------
%index
ginfo_sy
画面の初期化Yサイズ

%group
システム変数

%inst
現在の操作先ウィンドウの初期化Yサイズが代入されています。
(最初にscreen,bgscr,buffer命令で初期化された画面サイズになります。)
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_winx
ginfo

;---------------------------------------------------------------------
%index
ginfo_mesx
メッセージの出力Xサイズ

%group
システム変数

%inst
最後にmes, print命令により出力されたメッセージのXサイズが代入されています。
サイズは、 X座標にどれだけのドット数で描画されたかを示します。
画面上の絶対座標ではないので注意してください。
また、複数行ある文字列を出力した場合は、最後の行にあたるサイズが取得されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_mesy
ginfo

;---------------------------------------------------------------------
%index
ginfo_mesy
メッセージの出力Yサイズ

%group
システム変数

%inst
最後にmes, print命令により出力されたメッセージのYサイズが代入されています。
サイズは、 Y座標にどれだけのドット数で描画されたかを示します。
画面上の絶対座標ではないので注意してください。
また、複数行ある文字列を出力した場合は、最後の行にあたるサイズが取得されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_mesx
ginfo

;---------------------------------------------------------------------
%index
ginfo_r
現在設定されているカラーコードR

%group
システム変数

%inst
color命令などにより指定された赤の色コード(輝度)が代入されています。
色コードは、0〜255までの整数値になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_g
ginfo_b
ginfo

;---------------------------------------------------------------------
%index
ginfo_g
現在設定されているカラーコードG

%group
システム変数

%inst
color命令などにより指定された緑の色コード(輝度)が代入されています。
色コードは、0〜255までの整数値になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_r
ginfo_b
ginfo

;---------------------------------------------------------------------
%index
ginfo_b
現在設定されているカラーコードB

%group
システム変数

%inst
color命令などにより指定された青の色コード(輝度)が代入されています。
色コードは、0〜255までの整数値になります。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_r
ginfo_g
ginfo

;---------------------------------------------------------------------
%index
ginfo_paluse
デスクトップのカラーモード

%group
システム変数

%inst
現在のデスクトップカラーモード(色モード)が代入されています。
フルカラーモードの場合は0が、パレットモードの場合は1が返されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo

;---------------------------------------------------------------------
%index
ginfo_dispx
デスクトップ全体のXサイズ

%group
システム変数

%inst
デスクトップ全体のサイズ(画面解像度)が代入されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_dispy
ginfo

;---------------------------------------------------------------------
%index
ginfo_dispy
デスクトップ全体のYサイズ

%group
システム変数

%inst
デスクトップ全体のサイズ(画面解像度)が代入されています。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_dispx
ginfo

;---------------------------------------------------------------------
%index
ginfo_cx
カレントポジションのX座標

%group
システム変数

%inst
pos命令により設定されたカレントポジションのX座標が代入されています。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_cy
ginfo

;---------------------------------------------------------------------
%index
ginfo_cy
カレントポジションのY座標

%group
システム変数

%inst
pos命令により設定されたカレントポジションのY座標が代入されています。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo_cx
ginfo

;---------------------------------------------------------------------
%index
ginfo_intid
メッセージ割り込み時のウィンドウID

%group
システム変数

%inst
oncmd命令により設定されたメッセージ割り込み時のウィンドウIDが代入されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
oncmd
ginfo

;---------------------------------------------------------------------
%index
ginfo_newid
未使用ウィンドウID

%group
システム変数

%inst
screen命令やbuffer命令などで初期化されていない未使用のウィンドウIDが返されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
ginfo

;---------------------------------------------------------------------
%index
dir_cur
カレントディレクトリ(フォルダ)

%group
システム変数

%inst
現在のカレントディレクトリ(フォルダ)が代入されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
dirinfo

;---------------------------------------------------------------------
%index
dir_exe
実行ファイルがあるディレクトリ(フォルダ)

%group
システム変数

%inst
ランタイム実行ファイルがあるディレクトリ(フォルダ)が代入されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
dirinfo

;---------------------------------------------------------------------
%index
dir_win
Windowsディレクトリ(フォルダ)

%group
システム変数

%inst
Windowsがインストールされているディレクトリ(フォルダ)が代入されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
dirinfo

;---------------------------------------------------------------------
%index
dir_sys
Windowsシステムディレクトリ(フォルダ)

%group
システム変数

%inst
Windowsのシステムディレクトリ(フォルダ)が代入されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
dirinfo

;---------------------------------------------------------------------
%index
dir_cmdline
コマンドライン文字列

%group
システム変数

%inst
実行時に渡されたコマンドライン文字列が代入されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
dirinfo

;---------------------------------------------------------------------
%index
dir_desktop
デスクトップディレクトリ(フォルダ)

%group
システム変数

%inst
デスクトップディレクトリ(フォルダ)が代入されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
dirinfo

;---------------------------------------------------------------------
%index
dir_mydoc
マイドキュメントディレクトリ(フォルダ)

%group
システム変数

%inst
マイドキュメントディレクトリ(フォルダ)が代入されます。
^
※このシステム変数は、マクロとしてhspdef.as内で定義されています。

%href
dirinfo

;---------------------------------------------------------------------
