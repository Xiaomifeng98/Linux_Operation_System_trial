for name in 1001 1002 1003 1004 1005 1006 1007 1008 1009 1010
do 
sudo useradd stu$name
sudo echo "stu$name:stu$name"|sudo chpasswd
sudo usermod -a -G ua stu$name
done
