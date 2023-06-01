import paramiko
import threading

# function to get config and save it to file
def save_config(ip, username, password, cfile):
    try:
        # create ssh client
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(hostname=ip, username=username, password=password, timeout=5)

        # get config
        stdin, stdout, stderr = ssh.exec_command('export show-sensitive')
        config = stdout.read()
        # print(config)
        config_str = config.decode()
        config_str = config_str.replace("\\\r\n    ", "")
        config_str = config_str.replace("\r\n", "\n")
        if("expected end of command" in config_str):
            stdin, stdout, stderr = ssh.exec_command('export')
            config = stdout.read()
            config_str = config.decode()
            config_str = config_str.replace("\\\r\n    ", "")
            config_str = config_str.replace("\r\n", "\n")
        # save config to file
        with open(f'{cfile}/{ip}.rsc', 'w') as f:
            f.write(config_str)
        ssh.close()
    except:
        pass

def save_configs_all(ips, username, password, cfile):
    threads = []
    # start threads to get configs in parallel
    for ip in ips:
        t = threading.Thread(target=save_config, args=(ip, username, password, cfile))
        t.start()
        threads.append(t)

    # wait for all threads to finish
    for t in threads:
        t.join(10)

