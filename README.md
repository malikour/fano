# fano
Simple file anonymizer.
Replace all IP address and strings from a file.
Strings to replace are in /etc/dic
If you want to keep some IP address visible, you can put them in the whitelist dictionnary /etc/dic.wl 
<pre>
# cat toto
10.131.59.254
10.131.59.253
hostA
hostB

# ./fano
Usage:
Usage :
-f file         : mask a file , base on dictionary /etc/dic and white list /etc/dic.wl
-d dic          : specify an other dictionary to use ( instead of /etc/dic )
-n              : don't mask IP address
-h              : display help
-v              : display the version

# cat /etc/dic
user1
hostA
user34
domain.com

# cat /etc/dic.wl
10.131.59.254
10.131.49.254

# ./fano -f toto
White List = /etc/dic.wl
Begining of anonymization ..
2 modifications
End of anonymization
Anonymized file is toto.ano

# cat toto.ano
10.131.59.254
XXXXXXXXXXXXX
XXXXX
hostB

# 
</pre>
