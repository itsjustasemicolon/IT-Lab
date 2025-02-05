
## Easy-to-Understand Linux Network Commands  
*(Beginners' Guide)*

---

### **a. `ifconfig`** ⚠️ (Old Tool)  
**What it does**: Shows your computer's internet connections  
```bash
ifconfig          # See active network cards  
ifconfig eth0 up  # Turn on Wi-Fi/Ethernet (like flipping a switch)
```

---

### **b. `traceroute`**  
**What it does**: Shows the path your internet traffic takes  
```bash
traceroute google.com  # "Follow the road" to Google's servers
```

---

### **c. `ping`**  
**What it does**: Check if a website/device is reachable  
```bash
ping google.com        # Keep sending "Hello?" to Google  
ping -c 4 192.168.1.1 # Send 4 "Hello?" messages
```

---

### **d. `dig`**  
**What it does**: Look up website addresses (like phone book)  
```bash
dig google.com         # "What's Google's phone number?"
```

---

### **e. `telnet`** ⚠️ (Unsafe)  
**What it does**: Old way to connect to websites (*Use SSH instead*)  
```bash
telnet google.com 80  # "Knock on Google's door" (port 80)
```

---

### **f. `nslookup`**  
**What it does**: Find website's IP address (older method)  
```bash
nslookup google.com  # "What number is Google?"
```

---

### **g. `netstat`** ⚠️  
**What it does**: See active internet connections (*New tool: `ss`*)  
```bash
netstat -tuln  # "Who's talking to our computer right now?"
```

---

### **h. `scp`**  
**What it does**: Send files securely between computers  
```bash
scp photo.jpg user@friendspc:/pictures  # Email a file directly
```

---

### **i. `w`**  
**What it does**: See who's using the computer  
```bash
w  # "Who's logged in and what are they doing?"
```

---

### **j. `nmap`**  
**What it does**: Check which doors (ports) are open on a device  
```bash
nmap 192.168.1.1  # "What rooms are available in this house?"
```

---

### **k. `ifup`/`ifdown`**  
**What it does**: Turn internet connection on/off  
```bash
ifup eth0    # Plug in the cable  
ifdown eth0  # Unplug the cable
```

---

### **l. `route`** ⚠️  
**What it does**: Show directions for internet traffic (*Use `ip route`*)  
```bash
route -n  # "Map of all internet roads"
```

---

### **m. `host`**  
**What it does**: Simple website address lookup  
```bash
host google.com  # "Quick, Google's number please!"
```

---

### **n. `arp`** ⚠️  
**What it does**: List nearby devices on your network (*Use `ip neigh`*)  
```bash
arp -a  # "Who's in my neighborhood?"
```

---

### **o. `ethtool`**  
**What it does**: Check your cable internet speed/settings  
```bash
ethtool eth0  # "How fast is my wired connection?"
```

---

### **p. `iwconfig`** ⚠️  
**What it does**: Configure Wi-Fi (*New tool: `iw`*)  
```bash
iwconfig wlan0 essid "CoffeeShopWiFi"  # Connect to Wi-Fi
```

---

### **q. `system-config-network`**  
**What it does**: Simple network settings menu (text mode)

---

### **r. `bmon`**  
**What it does**: Live internet speed meter  
```bash
bmon  # "How much data am I using right now?"
```

---

### **s. `ssh`**  
**What it does**: Control another computer securely  
```bash
ssh me@officepc  # "Remote control my work computer"
```

---

### **t. `tcpdump`**  
**What it does**: Capture internet traffic (like phone tap)  
```bash
tcpdump -i eth0  # "Record all network conversations"
```

---

### **u. `dstat`**  
**What it does**: Computer health dashboard  
```bash
dstat -n  # "How's my network doing?"
```

---

### **v. `dhclient`**  
**What it does**: Get automatic internet settings  
```bash
dhclient eth0  # "Hey router, give me an IP address!"
```

---

### **w. `nload`**  
**What it does**: Live speedometer for your internet  
```bash
nload  # "How fast is my download RIGHT NOW?"
```

---

### **x. `iftop`**  
**What it does**: See who's using your bandwidth  
```bash
iftop  # "Which app is eating my internet?"
```

---

### **y. `ip`** (Modern Tool)  
**What it does**: Manage internet connections & addresses  
```bash
ip addr show  # "List all network cards and their numbers"
```

---

### **z. `route`** ⚠️  
*(Same as entry l - old map tool)*

---

### **aa. `iptables`** ⚠️  
**What it does**: Firewall rules (*New system: `nftables`*)  
```bash
iptables -L  # "List security rules"
```

---

### **bb. `sftp`**  
**What it does**: Send files securely (better than email)  
```bash
sftp me@fileserver  # "Secure file sharing"
```

---

### **cc. `socat`**  
**What it does**: Connect two internet services  
```bash
socat TCP4-LISTEN:1234,fork TCP4:10.0.0.5:5678  # "Network bridge"
```

---

### **dd. `rsync`**  
**What it does**: Smart file copying (only send changes)  
```bash
rsync -av photos/ backupdrive:/  # "Smart backup"
```

---

### **ee. `wget`**  
**What it does**: Download files from internet  
```bash
wget https://example.com/movie.mp4  # "Save online file"
```

---

### **ff. `curl`**  
**What it does**: Send/receive data from websites  
```bash
curl https://weather.com  # "Get website content"
```

---

**Key Symbols**:  
⚠️ = Older tool - try modern alternatives first  
🔒 = Uses encryption  
📡 = Wireless-related  
