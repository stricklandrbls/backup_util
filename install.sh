#!/bin/bash
config_dir='/etc/backup-util'

function print () {
    echo "[ ] $1"
}
function err () {
    echo "[!] $1"
}
function success () {
    echo "[+] $1"
}
function setup {

    if [ -d "$config_dir" ]; then
        print "directory \"$config_dir\" exists"
        if [ -f "$config_dir/config.json" ]; then
          err "Config file already exists!"
        else
            print "Creating config file"
            # touch $config_dir'/config.json'
            mv "config.json" $config_dir
      fi
      
    else
        print "Creating config directory"
        mkdir $config_dir
        print "Creating config file"
        # touch $config_dir'/config.json'
        mv "config.json" $config_dir
    fi

}

if [[ $EUID != 0 ]]; then
    err "You must be root to install!"
else
    setup
    success "Done!"
fi
