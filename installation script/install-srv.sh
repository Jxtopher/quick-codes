# VAR
URI="https://raw.githubusercontent.com/Jxtopher/config/main"
USER=""
RSA_KEY_PUB=""

# Check root
if [ $(whoami) != "root" ] ; then
  >&2 echo "[-] Need to be root"
  exit 1
fi

# OS Check
source /etc/os-release
if ! [[ "$VERSION_ID" =~ ^(11|10)$ ]] || ! [ "$ID" = 'debian' ] ; then
  >&2 echo "[-] Bad os version, only debian 10 and 10"
  exit 1
fi

# Install screen
apt-get -qq install -y screen
wget -nv $URI/.screenrc -O /etc/screenrc

# vim
apt-get -qq install -y vim
wget -nv $URI/vimrc -O /etc/vimrc

# Privilage
if ! [ -z "$USER" ] && grep -q "$USER:" /etc/passwd ; then
  apt-get -qq install -y sudo

  chmod 660 /etc/sudoers
  echo "$USER   ALL=(ALL:ALL) ALL" > /etc/sudoers
  chmod 440 /etc/sudoers

  if ! [ -z "$RSA_KEY_PUB" ] ; then
    # sshd
    apt-get -qq install -y openssh-server
    wget -nv $URI/sshd_config -O /etc/ssh/sshd_config
    systemctl restart sshd

    PATH_AUTHORIZED_KEYS="/home/$USER/.ssh/authorized_keys"
    if [ ! -f $PATH_AUTHORIZED_KEYS ]; then
        mkdir -p "/home/$USER/.ssh/" && touch $PATH_AUTHORIZED_KEYS
    fi

    if ! grep -q "$RSA_KEY_PUB" $PATH_AUTHORIZED_KEYS ; then
      echo $RSA_KEY_PUB > /home/chris/.ssh/authorized_keys
    fi
  fi
else
  >&2 echo "[-] User $USER not found"
fi

# nftables
wget -nv $URI/nftables.conf -O /etc/nftables.conf
systemctl restart nftables

# Information
echo "[+] Test the configuration and connect by ssh"
