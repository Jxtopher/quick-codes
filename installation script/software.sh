#!/bin/sh

sudo apt-get update
sudo apt-get upgrade -y

sudo apt-get install -y gparted unetbootin
#sudo apt-get swfdec-mozilla
#sudo apt-get install -y chromium-browser
sudo apt-get install -y openssh-server #fail2ban ulogd
sudo apt-get install -y clamav klamav
sudo apt-get install -y fdupes
#sudo apt-get install -y wine

#sudo apt-get install -y checkinstall
#sudo apt-get install -y subversion
#sudo apt-get install -y codeblocks
#sudo apt-get install -y eclipse
sudo apt-get install -y build-essential cmake wget # qtcreator
sudo apt-get install -y libboost-all-dev libcppunit-dev doxygen graphviz ccache
sudo apt-get install -y podbrowser
sudo apt-get install -y radare2
#sudo apt-get install -y qt-sdk

#sudo apt-get install -y compizconfig-settings-manager

#sudo apt-get install -y filezilla
#sudo apt-get install -y thunderbird

sudo apt-get install -y moc
sudo apt-get install -y vlc #vlc-plugin-esd mozilla-plugin-vlc
sudo apt-get install -y mplayer gnome-mplayer soundconverter

#sudo apt-get install -y conky
#sudo apt-get install -y alltray keepassx
sudo apt-get install -y gimp krita #blender
sudo apt-get install -y rar unrar
sudo apt-get install -y screen

sudo apt-get install acidrip soundconverter

echo "+--------------------------------------------------------+"
echo "|               Messagerie instantanée                   |"
echo "+--------------------------------------------------------+"
sudo apt-get install -y emesene irssi #weechat amsn

echo "+--------------------------------------------------------+"
echo "|       Wireshark est un analyseaur de protocole         |"
echo "+--------------------------------------------------------+"
sudo apt-get install -y wireshark iftop ngrep htop
sudo apt-get install -y nmap zenmap

echo "+--------------------------------------------------------+"
echo "|      Downloader for X (ou D4X) est un                  |"
echo "| gestionnaire/accélérateur de téléchargements           |"
echo "| https://addons.mozilla.org/fr/firefox/addon/220?id=220 |"
echo "| https://addons.mozilla.org/fr/firefox/addon/26         |"
echo "+--------------------------------------------------------+"
#sudo apt-get install -y d4x

echo "+--------------------------------------------------------+"
echo "|   Gqview permet de visionner et classer vos photo      |"
echo "+--------------------------------------------------------+"
#sudo apt-get install -y gqview

echo "+--------------------------------------------------------+"
echo "|           k3b permet la Gravure avancée                |"
echo "+--------------------------------------------------------+"
#sudo apt-get install -y k3b

echo "+--------------------------------------------------------+"
echo "|                      kdbg                              |"
echo "+--------------------------------------------------------+"
#sudo apt-get install -y kdbg

echo "+--------------------------------------------------------+"
echo "|                     ghex                               |"
echo "+--------------------------------------------------------+"
sudo apt-get install -y ghex

#echo "+--------------------------------------------------------+"
#echo "|                 virtualbox                             |"
#echo "+--------------------------------------------------------+"
#sudo apt-get install -y virtualbox-ose

echo "+--------------------------------------------------------+"
echo "|                      ghex                              |"
echo "+--------------------------------------------------------+"
sudo apt-get install -y texlive-base texlive-fonts-recommended-doc texlive-fonts-recommended texlive-full texlive-generic-recommended texlive-latex-base-doc texlive-latex-base texlive-latex-recommended-doc texlive-latex-recommended texlive-luatex texlive-metapost-doc texlive-metapost texlive-omega texlive-pictures-doc texlive-pictures texlive-xetex texlive texlive-binaries texlive-doc-base texlive-doc-en texlive-doc-fr texlive-bibtex-extra texlive-extra-utils texlive-font-utils texlive-fonts-extra-doc texlive-fonts-extra texlive-formats-extra texlive-games texlive-generic-extra texlive-humanities-doc texlive-humanities texlive-latex-extra-doc texlive-latex-extra texlive-latex3 texlive-math-extra texlive-music texlive-plain-extra texlive-pstricks-doc texlive-pstricks texlive-publishers-doc texlive-publishers texlive-science-doc texlive-science texlive-lang-all
sudo apt-get install -y wordnet
sudo apt-get install -y vim gvim xmind

sudo apt-get install -y git

#sudo apt-get install -y openttd
sudo apt-get install -y wxmaxima golly

sudo apt-get install qgis python-qgis
