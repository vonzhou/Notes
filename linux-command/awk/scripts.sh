	 vi scripts.sh 
	 fc -l > scripts.sh
	 awk '{gsub("ms","",$NF); if($NF > 100) print}' access.log 
	 awk '{gsub("ms","",$NF); if($NF > 100) print' access.log 
	 awk '{if($NF * 1 > threshhold) print}' threshhold=90 access.log 
	 awk '$NF * 1 > 80 &&  $(NF-1)*1 > 80 {print}' access.log 
	 awk '$NF > $(NF-1) {print}' access.log 
	 awk '$(NF-1) == 90 {print}' access.log 
	 awk '$(NF-1)*1 == 90 {print}' access.log 
	 awk '$4 !~ /192.168.0.4[1-5]/ {print }' access.log 
	 awk '$4 ~ /192.168.0.4[1-5]/ {print }' access.log 
	 man fc
	 fc -l
	 grep "192.168.0.4[1-5]" access.log | awk '{print $1}'
	 awk '/192.168.0.4[1-5]/{print $0}' access.log 
	 awk '/192.168.0.4[1-5]/{print $1}' access.log 
