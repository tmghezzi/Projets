#Sublimetext local/distant command 
#require pscp 

import sublime, sublime_plugin
import os
from subprocess import PIPE, Popen
def cmdline(command):
    process = subprocess.Popen(
        args=command,
        stdout=PIPE,
        shell=True
    )
    return process.communicate()[0]

class SshCmdCommand(sublime_plugin.TextCommand):
    def run(self, edit):
    	self.view.run_command('save')
        fileName = os.path.basename(self.view.file_name())
        pathName = os.path.dirname(self.view.file_name())
        os.chdir(pathName)
        #replace your_pwd by your password and galois@127.0.0.1:/usr/home/galois by your local/distant machine
        cmdstr = "pscp -pw your_pwd -P 2222 "+fileName+" galois@127.0.0.1:/usr/home/galois"
        print cmdstr
        cmdline(cmdstr)
