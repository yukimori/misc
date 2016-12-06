# install
http://qiita.com/kagutitan/items/57c829a1afb6b64ec65b
https://blog.ymyzk.com/2015/07/os-x-opencv-3-python-2-3/
 こちらの方が参考になるかも
 
scienceリポジトリにあるのでtapする必要がある
$ brew search opencv
homebrew/science/opencv    homebrew/science/opencv3
$ brew tap homebrew/science

brew install opencv3 --HEAD --with-python3
 # pip install numpy --with-python3でpython3を使ってnumpyをインストールしておくこと
   システムデフォルトのpython2を使ってnumpyをインストールしていると
   opencv3時に--with-python3を指定してもpython2の共有オブジェクトしか作成されないので注意する

macでは
QTkitがないとエラーになるので--HEADで対処版をインストールする

---- brewのメッセージで以下が出力される ----
opencv3 and opencv install many of the same files.

Generally there are no consequences of this for you. If you build your
own software and it requires this formula, you'll need to add to your
build variables:

    LDFLAGS:  -L/usr/local/opt/opencv3/lib
    CPPFLAGS: -I/usr/local/opt/opencv3/include
    PKG_CONFIG_PATH: /usr/local/opt/opencv3/lib/pkgconfig
-----------------------------------------

以下のディレクトリにシンボリックを作成する
$pwd
/Users/yukimori/.pyenv/versions/anaconda3-4.1.1/lib/python3.5/site-packages
$ln -s /usr/local/Cellar/opencv3/HEAD-30807b2_4/lib/python3.5/site-packages/cv2.cpython-35m-darwin.so ./
$ls cv2*
lrwxr-xr-x  1 yukimori  staff  94 11 19 00:56 cv2.cpython-35m-darwin.so -> /usr/local/Cellar/opencv3/HEAD-30807b2_4/lib/python3.5/site-packages/cv2.cpython-35m-darwin.so

import cv2が成功する

# imread/imshow
http://opencv.blog.jp/python/loadimage
http://qiita.com/supersaiakujin/items/54a4671142d80ca962ec

# camera
http://nonbiri-tereka.hatenablog.com/entry/2014/06/18/094614

cap = cv2.VideoCapture(0) 
while(cap.isOpened()):
   ret, frame = cap.read()
capでカメラを取り込む処理を行い、
readで一つひとつのフレームを読み込みます。

