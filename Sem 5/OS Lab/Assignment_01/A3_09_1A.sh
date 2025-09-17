#!/bin/bash
#
# Assignment No.: 1A
# Assignment Title: Familiarity with User and System level OS Commands
# Group No.: A3
# Team No.: 09
# Roll Nos.: 002311001004, 002311001011, 002311001049
# Member Names: Soham Das, Sarbo Sarcar, Arnob Bhakta

# Q1. who:-It displays the information about all the users who have logged into the system currently
# who
# (unknown) :0           2024-10-21 11:46 (:0)
# root     pts/0        2025-07-22 11:15 (172.16.5.159)
# be2304   pts/1        2025-07-22 15:47 (172.16.4.230)
# be2311   pts/3        2025-07-22 15:49 (172.16.4.231)
# be2314   pts/4        2025-07-22 16:06 (172.16.4.205)
# be2349   pts/6        2025-07-22 16:06 (172.16.4.218)
# be2382   pts/7        2025-07-22 16:06 (172.16.4.207)
# be2339   pts/8        2025-07-22 16:07 (172.16.4.216)
# be2337   pts/9        2025-07-22 16:07 (172.16.4.210)
# be2330   pts/10       2025-07-22 16:07 (172.16.4.203)
# be2392   pts/12       2025-07-22 16:08 (172.16.4.201)
# be2390   pts/13       2025-07-22 16:11 (172.16.4.212)
# be2350   pts/14       2025-07-22 16:12 (172.16.4.209)
# be2303   pts/15       2025-07-22 16:14 (172.16.4.227)
# be2342   pts/16       2025-07-22 16:19 (172.16.4.215)
# be2313   pts/18       2025-07-22 16:22 (172.16.4.228)
# be2317   pts/19       2025-07-22 16:25 (172.16.4.220)
# be2330   pts/20       2025-07-22 16:36 (172.16.4.203)

# Q2. whoami:- It displays Current username, Terminal number, date and time at which user logged into the system
# whoami
# be2311

# Q3. pwd:- It displays current working directory
# pwd
# /home/usr/student/ug/yr23/be2311/3rd Year/1st semester/OS

# Q4. date:- It displays system date and time
# date
# Tue Jul 22 16:39:52 IST 2025

# Q5. ls:- It lists the files and directories stored in the current directory.
# echo "The files/directories are:"; ls
# The files/directories are:
# A3_09_1A.sh

# Q6. mkdir:– It is used to create directories.
# mkdir sample; echo "Created 'sample' directory"; rmdir sample
# Created 'sample' directory

# Q7. clear:- It clears the screen
# clear; echo "Screen has been cleared!"
# Screen has been cleared!

# Q8. cd:- It is used to change the current working directory to any other directory specified
# mkdir sample; cd sample; echo "Moved to 'sample' directory"; cd ../; rmdir sample
# Moved to 'sample' directory

# Q9. df:- It displays currently mounted file systems.
# df
# Filesystem                   1K-blocks      Used  Available Use% Mounted on
# /dev/mapper/scientific-root   52399104  27794252   24604852  54% /
# devtmpfs                      32758584         0   32758584   0% /dev
# tmpfs                         32774652     10340   32764312   1% /dev/shm
# tmpfs                         32774652    789176   31985476   3% /run
# tmpfs                         32774652         0   32774652   0% /sys/fs/cgroup
# /dev/sda2                      1039616    238088     801528  23% /boot
# /dev/mapper/scientific-home 2256669952 136334316 2120335636   7% /home
# tmpfs                          6554932        16    6554916   1% /run/user/42
# tmpfs                          6554932         0    6554932   0% /run/user/3067
# tmpfs                          6554932         0    6554932   0% /run/user/3097
# tmpfs                          6554932         0    6554932   0% /run/user/3014
# tmpfs                          6554932         0    6554932   0% /run/user/3107
# tmpfs                          6554932         0    6554932   0% /run/user/3218
# tmpfs                          6554932         0    6554932   0% /run/user/3213
# tmpfs                          6554932         0    6554932   0% /run/user/3271
# tmpfs                          6554932         0    6554932   0% /run/user/3292
# tmpfs                          6554932         0    6554932   0% /run/user/3211
# tmpfs                          6554932         0    6554932   0% /run/user/3209
# tmpfs                          6554932         0    6554932   0% /run/user/3223
# tmpfs                          6554932         0    6554932   0% /run/user/3275
# tmpfs                          6554932         0    6554932   0% /run/user/0
# tmpfs                          6554932         0    6554932   0% /run/user/3207
# tmpfs                          6554932         0    6554932   0% /run/user/3214
# tmpfs                          6554932         0    6554932   0% /run/user/3285
# tmpfs                          6554932         0    6554932   0% /run/user/3242
# tmpfs                          6554932         0    6554932   0% /run/user/3240
# tmpfs                          6554932         0    6554932   0% /run/user/3233
# tmpfs                          6554932         0    6554932   0% /run/user/3295
# tmpfs                          6554932         0    6554932   0% /run/user/3293
# tmpfs                          6554932         0    6554932   0% /run/user/3253
# tmpfs                          6554932         0    6554932   0% /run/user/3206
# tmpfs                          6554932         0    6554932   0% /run/user/3245
# tmpfs                          6554932         0    6554932   0% /run/user/3216
# tmpfs                          6554932         0    6554932   0% /run/user/3217
# tmpfs                          6554932         0    6554932   0% /run/user/3297
# tmpfs                          6554932         0    6554932   0% /run/user/3267
# tmpfs                          6554932         0    6554932   0% /run/user/3288

# Q10. rmdir:- Directories can be deleted using the rmdir command
# mkdir sample; echo "Created 'sample' directory"; rmdir sample; echo "Removed 'sample' directory"
# Created 'sample' directory
# Removed 'sample' directory

# Q11. cat:– It displays the contents of a file
# echo "This is a sample file with text" >> a.txt; cat a.txt; rm a.txt
# This is a sample file with text

# Q12. cp:- It is used to copy a file
# echo "Hello" >> a.txt; echo "Created file a.txt with contents: $(cat a.txt)"; cp a.txt b.txt; echo -e "Copied a.txt to b.txt\nContents of b.txt: $(cat b.txt)"; rm *.txt
# Created file a.txt with contents: Hello
# Copied a.txt to b.txt
# Contents of b.txt: Hello

# Q13. mv:- It is used to change the name of a file
# echo "Hello" >> a.txt; echo -e "Contents of a.txt: $(cat a.txt)\nRenaming to b.txt"; mv a.txt b.txt; echo "Contents of b.txt: $(cat b.txt)"; rm *.txt
# Contents of a.txt: Hello
# Renaming to b.txt
# Contents of b.txt: Hello

# Q14. rm:- It is used to delete an existing file
# touch a.txt; rm a.txt; echo "Deleted a file 'a.txt' after creation"
# Deleted a file 'a.txt' after creation

# Q15. stat:- It is used to display file or file system status
# touch a.txt; stat a.txt; rm a.txt
#   File: ‘a.txt’
#   Size: 0               Blocks: 0          IO Block: 4096   regular empty file
# Device: fd02h/64770d    Inode: 8321693233  Links: 1
# Access: (0644/-rw-r--r--)  Uid: ( 3214/  be2311)   Gid: ( 2926/  ugyr23)
# Context: unconfined_u:object_r:user_home_t:s0
# Access: 2025-07-22 17:38:56.832889651 +0530
# Modify: 2025-07-22 17:38:56.832889651 +0530
# Change: 2025-07-22 17:38:56.832889651 +0530
#  Birth: -

# Q16. ln:- It is used to create links between files and directories.
# touch a.txt; ln a.txt my_file; echo "Created a hard link named 'my_file' to file 'a.txt'"; rm a.txt my_file
# Created a hard link named 'my_file' to file 'a.txt'

# Q17. tty:- It prints the filename of the terminal connected to standard input.
# tty
# /dev/pts/3


# 18) uname –It prints system information
# uname -a
# Linux asus-laptop 6.11.0-29-generic #29~24.04.1-Ubuntu SMP PREEMPT_DYNAMIC Thu Jun 26 14:16:59 UTC 2 x86_64 x86_64 x86_64 GNU/Linux


# 19) umask – It specifies user file creation mask, implying which of the 3 permissions are to be denied to the owner,group and others.
# umask
# 002


# 20) find – It searches for files in a directory hierarchy
# mkdir folder{1..10} && touch folder{1..10}/file{1..5} && find . -name 'file1' && rm -rf folder{1..10}
#./folder9/file1
#./folder3/file1
#./folder10/file1
#./folder2/file1
#./folder1/file1
#./folder6/file1
#./folder7/file1
#./folder4/file1
#./folder5/file1
#./folder8/file1


# 21) sort – It sorts the lines of text files
# echo -e "\n==before sorting==\n" && cat /etc/os-release && echo -e "\n==after sorting==\n" && cat /etc/os-release | sort
#
#==before sorting==
#
#PRETTY_NAME="Ubuntu 24.04.2 LTS"
#NAME="Ubuntu"
#VERSION_ID="24.04"
#VERSION="24.04.2 LTS (Noble Numbat)"
#VERSION_CODENAME=noble
#ID=ubuntu
#ID_LIKE=debian
#HOME_URL="https://www.ubuntu.com/"
#SUPPORT_URL="https://help.ubuntu.com/"
#BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
#PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
#UBUNTU_CODENAME=noble
#LOGO=ubuntu-logo
#
#==after sorting==
#
#BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
#HOME_URL="https://www.ubuntu.com/"
#ID_LIKE=debian
#ID=ubuntu
#LOGO=ubuntu-logo
#NAME="Ubuntu"
#PRETTY_NAME="Ubuntu 24.04.2 LTS"
#PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
#SUPPORT_URL="https://help.ubuntu.com/"
#UBUNTU_CODENAME=noble
#VERSION="24.04.2 LTS (Noble Numbat)"
#VERSION_CODENAME=noble
#VERSION_ID="24.04"


# 22) ps - It displays information about the current processes.
# ps -a
#    PID TTY          TIME CMD
#   5212 pts/0    00:00:00 nvim
#   8714 pts/1    00:00:00 tmux: client
#  11806 pts/17   00:00:00 ps


# 23) chmod 777 file1 - gives full permission to owner, group and others
# touch somefile && echo "\n --- initial permissions ---\n" && ls -la | grep somefile && chmod 777 somefile && echo "\n\n --- permissions after setting 777 ---\n" && ls -la | grep somefile && rm -rf somefile
#
#
# --- initial permissions ---
#
#-rw-rw-r--  1 user user     0 Jul 23 23:19 somefile
#
#
# --- permissions after setting 777 ---
#
#-rwxrwxrwx  1 user user     0 Jul 23 23:19 somefile



# 24) grep - It finds specific patterns in files.
# cat /etc/os-release | grep VERSION
# VERSION_ID="24.04"
# VERSION="24.04.2 LTS (Noble Numbat)"
# VERSION_CODENAME=noble


# 25) touch - It creates an empty file or updates the timestamp of an existing file.
# ls && echo "\n\n == creating new file name "newFile" using touch  == \n" && touch newFile && ls -la | grep newFile && echo "\n\n == changing the date to jan 1 2030 == " && touch -t 203001010000 newFile && ls -la | grep newFile && rm -rf newFile
#
#
# == creating new file name newFile using touch  ==
#
#-rw-rw-r--  1 user user     0 Jul 23 23:27 newFile
#
#
# == changing the date to jan 1 2030 ==
#-rw-rw-r--  1 user user     0 Jan  1  2030 newFile


# 26) more/less - It displays file content one screen at a time, allowing you to scroll.
# echo -e " == opening in more == " && sleep 2 && ps -aux | less && clear && echo -e " == opening in more == " && sleep 2 && ps -aux | more
# == opening in less ==
#
#USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
#root           1  0.1  0.0  24168 14472 ?        Ss   23:12   0:02 /sbin/init splash
#root           2  0.0  0.0      0     0 ?        S    23:12   0:00 [kthreadd]
#root           3  0.0  0.0      0     0 ?        S    23:12   0:00 [pool_workqueue_release]
#root           4  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-rcu_gp]
#root           5  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-sync_wq]
#root           6  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-slub_flushwq]
#root           7  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-netns]
#root           9  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/0:0H-events_highpri]
#:
#
# == opening in more ==
#USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
#root           1  0.1  0.0  24168 14472 ?        Ss   23:12   0:02 /sbin/init splash
#root           2  0.0  0.0      0     0 ?        S    23:12   0:00 [kthreadd]
#root           3  0.0  0.0      0     0 ?        S    23:12   0:00 [pool_workqueue_release]
#root           4  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-rcu_gp]
#root           5  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-sync_wq]
#root           6  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-slub_flushwq]
#root           7  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-netns]
#root           9  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/0:0H-events_highpri]
# --More--


# 27) head/tail - It displays First/Last 10 lines of a File.
# echo -e "\n\n== head == \n" && ps -aux | head && echo -e " \n\n== tail == \n" && ps -aux | tail
#
#
#== head ==
#
#USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
#root           1  0.1  0.0  24168 14472 ?        Ss   23:12   0:02 /sbin/init splash
#root           2  0.0  0.0      0     0 ?        S    23:12   0:00 [kthreadd]
#root           3  0.0  0.0      0     0 ?        S    23:12   0:00 [pool_workqueue_release]
#root           4  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-rcu_gp]
#root           5  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-sync_wq]
#root           6  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-slub_flushwq]
#root           7  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/R-netns]
#root           9  0.0  0.0      0     0 ?        I<   23:12   0:00 [kworker/0:0H-events_highpri]
#root          10  0.0  0.0      0     0 ?        I    23:12   0:00 [kworker/0:1-events]
#
#
#== tail ==
#
#root       12341  0.0  0.0      0     0 ?        I    23:26   0:00 [kworker/5:0-mm_percpu_wq]
#root       12445  0.0  0.0      0     0 ?        I    23:27   0:00 [kworker/0:0-cgroup_destroy]
#root       12841  0.2  0.0      0     0 ?        I    23:31   0:00 [kworker/u64:2-events_unbound]
#root       13311  0.1  0.2 481656 43572 ?        Ssl  23:32   0:00 /usr/libexec/fwupd/fwupd
#root       13319  0.0  0.0      0     0 ?        I    23:32   0:00 [kworker/8:1-i915-unordered]
#root       13320  0.0  0.0      0     0 ?        I    23:32   0:00 [kworker/4:0]
#root       13323  0.0  0.0      0     0 ?        I    23:32   0:00 [kworker/2:2-cgroup_destroy]
#user       14304  0.0  0.0  15236  5600 pts/3    R+   23:36   0:00 ps -aux
#user       14305  0.0  0.0   8320  1840 pts/3    S+   23:36   0:00 tail


# 28) top - It dynamically displays real-time information about system statistics.
# top
#top - 23:39:57 up 27 min,  1 user,  load average: 0.61, 0.67, 0.63
#Tasks: 365 total,   3 running, 360 sleeping,   2 stopped,   0 zombie
#%Cpu(s):  2.9 us,  1.7 sy,  0.0 ni, 95.4 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
#MiB Mem :  15615.8 total,   7839.9 free,   5015.1 used,   4064.7 buff/cache
#MiB Swap:   4096.0 total,   4096.0 free,      0.0 used.  10600.7 avail Mem
#
#    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
#   9164 user      20   0 2998624 300548 113172 S  36.4   1.9   1:26.33 Isolated Web Co
#   4212 user      20   0   12.1g 509084 228008 R   9.1   3.2   2:05.13 firefox
#   4892 user      20   0 2814556 346408 116796 S   9.1   2.2   1:34.11 Isolated Web Co
#   9245 user      20   0 2883036 352764 120848 R   9.1   2.2   0:54.00 Isolated Web Co
#  14362 root      20   0       0      0      0 D   9.1   0.0   0:00.13 kworker/u64:3+events_unbound
#      1 root      20   0   24168  14472   9096 S   0.0   0.1   0:02.09 systemd
#      2 root      20   0       0      0      0 S   0.0   0.0   0:00.00 kthreadd
#      3 root      20   0       0      0      0 S   0.0   0.0   0:00.00 pool_workqueue_release


# 29) kill - It terminates a Process.
#echo -e " == creating a sleep process for 50 sec == " &&  sleep 50 & sleep_pid=$! && ps && echo -e "\n== killing the process ==\n" && kill -9 $sleep_pid
# == creating a sleep process for 50 sec ==
#[1] 18477
#    PID TTY          TIME CMD
#  15232 pts/3    00:00:00 zsh
#  18477 pts/3    00:00:00 sleep
#  18478 pts/3    00:00:00 ps
#
#== killing the process ==
#
#[1]  + killed     sleep 50


# 30) history - It displays a list of previously executed commands.
#history
# 1601  whoami
# 1602  clear
# 1603  ls
# 1604  chsh -s $(which zsh)
# 1605  clear
# 1606  r
# 1607  exit
# 1608  ping google.com
# 1609  echo "hello world"
# 1610  echo "my name"
# 1611  clear


# 31) du - It estimates file space usage (of a file or directory).
#echo -e "== initial size of the current folder ==\n" && du -h . && echo -e "== creating 10 files with hello world written in them == \n"&& echo "hello world" >> newFile{1..10} && du -h . && rm -rf newFile{1..10}
#== initial size of the current folder ==
#
# 4.0K	.
#== creating 10 files with hello world written in them ==
#
#44K



# 32) ping - It tests network connectivity to a host.
# ping -c 4 google.com
#PING google.com (142.250.206.78) 56(84) bytes of data.
#64 bytes from pnmaaa-ay-in-f14.1e100.net (142.250.206.78): icmp_seq=1 ttl=118 time=91.0 ms
#64 bytes from pnmaaa-ay-in-f14.1e100.net (142.250.206.78): icmp_seq=2 ttl=118 time=114 ms
#64 bytes from pnmaaa-ay-in-f14.1e100.net (142.250.206.78): icmp_seq=3 ttl=118 time=136 ms
#64 bytes from pnmaaa-ay-in-f14.1e100.net (142.250.206.78): icmp_seq=4 ttl=118 time=158 ms
#
#--- google.com ping statistics ---
#4 packets transmitted, 4 received, 0% packet loss, time 3004ms
#rtt min/avg/max/mdev = 91.042/124.766/158.455/25.089 ms


# 33) wc - It counts lines, words, and characters in a file. order -> newline, word and byte count
#wc /etc/os-release
# 13  18 400 /etc/os-release


# 34) >/>> - It redirects the standard output of a command to a file, overwriting the file if it exists.
#touch newFile && echo "hello" > newFile && cat newFile && echo -e "\n== after appending ==\n" && echo " world" >> newFile && cat newFile && rm -rf newFile
#hello
#
#== after appending ==
#
#hello
# world


# 35) | - It takes the standard output of one command and uses it as the standard input for another
#cat /etc/os-release | head -n 3
#PRETTY_NAME="Ubuntu 24.04.2 LTS"
#NAME="Ubuntu"
#VERSION_ID="24.04"
