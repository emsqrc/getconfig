
import paramiko
import concurrent.futures
import time

import threading
import os
import shutil

def upload_config_to_device(device, username, password, local_file_path, remote_file_path, binfile):
    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(device, username=username, password=password, timeout=5)
        stdin, stdout, stderr = ssh.exec_command("ls")
        flash_folder_list = stdout.read().decode("utf-8").strip().split("\n")

        if "flash" in flash_folder_list:
            remote_file_path = "flash/" + remote_file_path

        sftp = ssh.open_sftp()
        if binfile!='none':#отправка файла
           sftp.put(f'send/{binfile}', binfile) 
        sftp.put(f'send/{device}.rsc', remote_file_path)
        sftp.close()
        # wait for file to appear on Mikrotik device
        file_exists = False
        while not file_exists:
            stdin, stdout, stderr = ssh.exec_command("file print")
            if remote_file_path in stdout.read().decode("utf-8"):
                file_exists = True
            else:
                time.sleep(1)
        # Adding the command to reset the configuration after uploading the file
        stdin, stdout, stderr = ssh.exec_command("/system reset-configuration no-defaults=yes run-after-reset=" + remote_file_path)
        stdin, stdout, stderr = ssh.exec_command("y")
        ssh.close()
        print(f"Config uploaded successfully to {device}")
        shutil.copy(f'send/{device}.rsc', f'{local_file_path}/{device}.rsc')
        os.remove(f'send/{device}.rsc')
    except:
        with open(f'errors/{device}.rsc', 'w') as f:
            pass

'''
def upload_config_to_devices(devices, username, password, local_file_path, remote_file_path):
    with concurrent.futures.ThreadPoolExecutor(max_workers=100) as executor:
        results = [executor.submit(upload_config_to_device, device, username, password, local_file_path, remote_file_path) for device in devices]
    for result in results:
        try:
            result.result(timeout=10)
        except:
            pass
'''
def upload_config_to_devices(devices, username, password, local_file_path, remote_file_path, binfile):
    threads = []
    # start threads to get configs in parallel
    for ip in devices:
        t = threading.Thread(target=upload_config_to_device, args=(ip, username, password, local_file_path, remote_file_path, binfile))
        t.start()
        threads.append(t)

    # wait for all threads to finish
    for t in threads:
        if binfile=='none':
            t.join(15)
        else:
            t.join(30)
'''
def send_cmd(ip, username, password, fcmd):
    try:
        # create ssh client
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(hostname=ip, username=username, password=password)
        with open(f'send/{ip}.rsc', 'r') as f:
            cmdstr=f.read()
            
            for line in f:
                # get config
                stdin, stdout, stderr = ssh.exec_command(line)
                config = stdout.read()
                print(line)
                print(config.decode())
            
        stdin, stdout, stderr = ssh.exec_command(cmdstr)
        config = stdout.read()
        print(config.decode())
        ssh.close()
        shutil.copy(f'send/{ip}.rsc', f'{fcmd}/{ip}.rsc')
        os.remove(f'send/{ip}.rsc')
    except:
        with open(f'errors/{ip}.rsc', 'w') as f:
            pass
'''

def send_cmd(device, username, password, local_file_path, binfile):
    try:
        remote_file_path = "cmd.rsc"
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(device, username=username, password=password, timeout=5)
        stdin, stdout, stderr = ssh.exec_command("ls")
        flash_folder_list = stdout.read().decode("utf-8").strip().split("\n")

        if "flash" in flash_folder_list:
            remote_file_path = "flash/" + remote_file_path

        sftp = ssh.open_sftp()
        if binfile!='none':#отправка файла
           sftp.put(f'send/{binfile}', binfile) 
        sftp.put(f'send/{device}.rsc', remote_file_path)
        sftp.close()
        # wait for file to appear on Mikrotik device
        file_exists = False
        while not file_exists:
            stdin, stdout, stderr = ssh.exec_command("file print")
            if remote_file_path in stdout.read().decode("utf-8"):
                file_exists = True
            else:
                time.sleep(1)
        # Adding the command to reset the configuration after uploading the file
        stdin, stdout, stderr = ssh.exec_command("import file-name=" + remote_file_path)
        ssh.close()
        print(f"Config uploaded successfully to {device}")
        shutil.copy(f'send/{device}.rsc', f'{local_file_path}/{device}.rsc')
        os.remove(f'send/{device}.rsc')
    except:
        with open(f'errors/{device}.rsc', 'w') as f:
            pass 

            

def send_cmd_all(ips, username, password, filecmd, binfile):
    threads = []
    # start threads to get configs in parallel
    for ip in ips:
        t = threading.Thread(target=send_cmd, args=(ip, username, password, filecmd, binfile))
        t.start()
        threads.append(t)

    # wait for all threads to finish
    for t in threads:
        if binfile=='none':
            t.join(15)
        else:
            t.join(30)