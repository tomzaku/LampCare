[uwsgi]
project = LampCare
base = /Volumes/GIT/web/

chdir = %(base)/%(project)/server
home = %(base)/envLamp/
module = %(project).wsgi:application