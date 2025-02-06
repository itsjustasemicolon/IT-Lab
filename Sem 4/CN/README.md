
## Linux Network Commands Guide  
*(Assignment 1)*
---

### **a. `ifconfig`** ⚠️  
**What it does**:  
Displays your computer's network cards (Ethernet/Wi-Fi) and their settings. Shows IP addresses and connection status.  
*Modern Alternative*: Use `ip addr` for more features  
```bash
ifconfig          # See active network cards  
ifconfig eth0 up  # Turn on Wi-Fi/Ethernet
```

---

### **b. `traceroute`**  
**What it does**:  
Reveals the path your data travels through routers to reach websites. Helps identify slow connection points.  
```bash
traceroute google.com  # Map route to Google
```

---

### **c. `ping`**  
**What it does**:  
Tests basic connection to websites/devices using "echo" signals. Checks if remote host is alive.  
```bash
ping google.com        # Continuous connection test  
ping -c 4 192.168.1.1 # Test 4 times then stop
```

---

### **d. `dig`**  
**What it does**:  
Looks up website server addresses like a digital phonebook. Shows hidden DNS details.  
```bash
dig google.com         # Full DNS information
```

---

### **e. `telnet`** ⚠️ (Unsafe)  
**What it does**:  
Unprotected connection tester. Can check if ports are open but sends data openly.  
```bash
telnet google.com 80  # Test website port 80
```

---

### **f. `nslookup`**  
**What it does**:  
Finds IP addresses for websites using your network's DNS settings.  
```bash
nslookup google.com  # Basic DNS query
```

---

### **g. `netstat`** ⚠️  
**What it does**:  
Lists active internet connections and programs using them.  
*Modern Alternative*: `ss -tuln`  
```bash
netstat -tuln  # Show listening ports
```

---

### **h. `scp`** 🔒  
**What it does**:  
Encrypted file transfer between computers using SSH security.  
```bash
scp photo.jpg user@friendspc:/pictures
```

---

### **i. `w`**  
**What it does**:  
Shows who's currently using the computer and their activities.  
```bash
w  # Active users overview
```

---

### **j. `nmap`**  
**What it does**:  
Scans devices to find open network ports (like checking doors/windows).  
```bash
nmap 192.168.1.1  # Basic port scan
```

---

### **k. `ifup`/`ifdown`**  
**What it does**:  
Safely connects/disconnects network cables virtually.  
```bash
ifup eth0    # Start connection  
ifdown eth0  # Stop connection
```

---

### **l. `route`** ⚠️  
**What it does**:  
Displays network path rules (like GPS for internet traffic).  
```bash
route -n  # Simplified routing table
```

---

### **m. `host`**  
**What it does**:  
Quick website address translation (name → IP address).  
```bash
host google.com  # Fast DNS lookup
```

---

### **n. `arp`** ⚠️  
**What it does**:  
Lists devices on your local network using physical addresses.  
```bash
arp -a  # Neighborhood device list
```

---

### **o. `ethtool`**  
**What it does**:  
Shows detailed wired internet connection specifications.  
```bash
ethtool eth0  # Cable connection details
```

---

### **p. `iwconfig`** 📡⚠️  
**What it does**:  
Configures basic WiFi settings (SSID/channel).  
```bash
iwconfig wlan0 essid "CoffeeShopWiFi"
```

---

### **q. `system-config-network`**  
**What it does**:  
Text menu for network setup (Red Hat systems).  
```bash
system-config-network  # Launch config UI
```

---

### **r. `bmon`**  
**What it does**:  
Live internet speed monitor with simple graphs.  
```bash
bmon  # Bandwidth dashboard
```

---

### **s. `ssh`** 🔒  
**What it does**:  
Secure remote computer control with encryption.  
```bash
ssh me@officepc  # Remote login
```

---

### **t. `tcpdump`**  
**What it does**:  
Network traffic recorder for advanced diagnostics.  
```bash
tcpdump -i eth0  # Capture all traffic
```

---

### **u. `dstat`**  
**What it does**:  
Combined system resource monitor (network+CPU+disk).  
```bash
dstat -n  # Network focus mode
```

---

### **v. `dhclient`**  
**What it does**:  
Automatically gets network settings from routers.  
```bash
dhclient eth0  # Request new IP
```

---

### **w. `nload`**  
**What it does**:  
Real-time upload/download speed display.  
```bash
nload  # Speedometer view
```

---

### **x. `iftop`**  
**What it does**:  
Shows which connections use most bandwidth.  
```bash
iftop  # Traffic breakdown
```

---

### **y. `ip`**  
**What it does**:  
Modern network configuration Swiss Army knife.  
```bash
ip addr show  # Interface overview
```

---

### **aa. `iptables`** ⚠️  
**What it does**:  
Firewall rule manager (security filter).  
```bash
iptables -L  # List rules
```

---

### **bb. `sftp`** 🔒  
**What it does**:  
Secure file browser with folder navigation.  
```bash
sftp me@fileserver  # Encrypted transfer
```

---

### **cc. `socat`**  
**What it does**:  
Network connector for advanced users.  
```bash
socat TCP4-LISTEN:1234,fork TCP4:target:5678
```

---

### **dd. `rsync`**  
**What it does**:  
Smart file sync that saves bandwidth.  
```bash
rsync -av photos/ backupdrive:/
```

---

### **ee. `wget`**  
**What it does**:  
Reliable file downloader with resume support.  
```bash
wget https://example.com/movie.mp4
```

---

### **ff. `curl`**  
**What it does**:  
Website interaction tool for developers.  
```bash
curl https://weather.com  # Get webpage
```

---

**Key**:  
⚠️ = Older tool | 🔒 = Encrypted | 📡 = Wireless  
