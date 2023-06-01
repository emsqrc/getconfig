
import ips
import getConfig
import analysis
#import showConfig
import setConfig
import sys
import os
import tl

ipl = ips.get_ips_from_file(sys.argv[2])
us = sys.argv[3]
pwd = sys.argv[4]

if os.path.isfile('res.txt'):
    os.remove('res.txt')

if sys.argv[1] == 'export':
    #ips.remove_rsc_files(sys.argv[5])
    getConfig.save_configs_all(ipl,us,pwd,sys.argv[5])
    r = analysis.find_missing_ips(ipl,sys.argv[5])
    with open(f'res.txt', 'w') as f:
        f.write('\n'.join(r))
elif sys.argv[1] == 'import':
    ips.remove_rsc_files('errors')
    setConfig.upload_config_to_devices(ipl,us,pwd,sys.argv[5],"newc.rsc",sys.argv[6])
    r = analysis.get_files_with_extension('errors','rsc')
    with open(f'res.txt', 'w') as f:
        f.write('\n'.join(r))
elif sys.argv[1] == 'send':
    ips.remove_rsc_files('errors')
    setConfig.send_cmd_all(ipl,us,pwd,sys.argv[5],sys.argv[6])
    r = analysis.get_files_with_extension('errors', 'rsc')
    with open(f'res.txt', 'w') as f:
        f.write('\n'.join(r))
elif sys.argv[1] == 'teleg':
    try:
        tl.send_telegram_message()
    except:
        pass
    
sys.exit()
os._exit()
