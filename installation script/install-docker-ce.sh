
# OS Check: Debian 11
source /etc/os-release
if ! [[ "$VERSION_ID" =~ ^(11)$ ]] || ! [ "$ID" = 'debian' ] ; then
  >&2 echo "[-] Bad os version, only debian 10 and 10"
  exit 1
fi


# Docker-ce engine
sudo apt-get update -y
sudo apt-get install -y apt-transport-https ca-certificates curl  gnupg lsb-release
curl -fsSL https://download.docker.com/linux/debian/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
echo \
"deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/debian \
$(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
sudo apt-get install -y docker-ce docker-ce-cli containerd.io


# Docker Compose
sudo apt-get install -y python3-dev libffi-dev libssl-dev gcc libc-dev  cargo  make
sudo curl -L "https://github.com/docker/compose/releases/download/1.29.2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
sudo ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose
docker-compose --version

# Create user docker
/usr/sbin/useradd -r -s  /bin/bash docker
