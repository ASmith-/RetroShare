RetroShare
==============================
RetroShare is a decentralized, private and secure commmunication and sharing platform. RetroShare provides filesharing, chat, messages, forums and channels. 

Compilation on Linux
----------------------------

1. Install package dependencies:
   * Debian/Ubuntu
   ```bash
   sudo apt-get install libglib2.0-dev libupnp-dev qt4-dev-tools \
       libqt4-dev libssl-dev libxss-dev libgnome-keyring-dev libbz2-dev \
       libqt4-opengl-dev libqtmultimediakit1 qtmobility-dev \
       libspeex-dev libspeexdsp-dev libxslt1-dev libcurl4-openssl-dev \
       libopencv-dev, tcl8.5, libmicrohttpd-dev
   ```
   * openSUSE
   ```bash
   sudo zypper install gcc-c++ libqt4-devel libgnome-keyring-devel \
       glib2-devel speex-devel libssh-devel protobuf-devel libcurl-devel \
       libxml2-devel libxslt-devel sqlcipher-devel libmicrohttpd-devel \
       opencv-devel speexdsp-devel libupnp-devel
   ```
   * Arch Linux
   ```bash
   pacman -S base-devel libgnome-keyring libmicrohttpd libupnp libxslt \
       libxss opencv qt4 speex sqlcipher
   ```

2. Checkout the source code
   ```bash
   mkdir ~/retroshare
   cd ~/retroshare 
   git clone https://github.com/RetroShare/RetroShare.git trunk
   ```

3. Compile
   ```bash
   cd trunk
   qmake CONFIG=debug
   make
   ```

   The executables produced will be:

         trunk/retroshare-gui/src/RetroShare
         trunk/retroshare-nogui/src/retroshare-nogui

If libsqlcipher is not available as a package
---------------------------------------------

You need to place sqlcipher so that the hierarchy is:

      retroshare
          |
          +--- trunk
          |
          +--- lib
                |
                +---- sqlcipher
```bash
mkdir lib
cd lib
git clone git://github.com/sqlcipher/sqlcipher.git
cd sqlcipher
./configure --enable-tempstore=yes CFLAGS="-DSQLITE_HAS_CODEC" LDFLAGS="-lcrypto"
make
cd ..
```

Using retroshare-nogui & webUI
------------------------------

The webUI needs to be enabled as a parameter option in retroshare-nogui:

```bash
./retroshare-nogui --webinterface 9090 --docroot /usr/share/RetroShare06/webui/
```

The webUI is only accessible on localhost:9090 (unless you canged that
option in the GUI). It is advised to keep it that way so that your RS
cannot be controlled using an untrusted connection.

To access your web UI from a distance, just open a SSH tunnel on it:

```bash
distant_machine:~/ >  ssh rs_host -L 9090:localhost:9090 -N
```

"rs_host" is the machine running retroshare-nogui. Then on the distant machine, access your webUI on 


      http://localhost:9090

That also works with a retroshare GUI of course.
