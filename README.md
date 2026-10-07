# 26_Robot Master_preview_storage_rebuild

## What is this storage for

* The storage is used to communicate while preparing for the competition.

## Why rebuild it

* The former storage belongs to a GitHub account signed in with a Gmail mailbox, which is quite difficult when the internet is pool. 
* So, I rebuild the storage with a GitHub account signed in with a QQ mailbox.

## What is in .gitignore

* gitignore now contains:

```txt
# ===== System =====
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db
desktop.ini
*~

# ===== Office / WPS temp&lock =====
~$*
*.tmp
.~lock.*#

# ===== editor / IDE =====
.vscode/*
!.vscode/settings.json
!.vscode/extensions.json
.idea/
*.swp
*.swo

# ===== build =====
node_modules/
dist/
build/
out/
__pycache__/
*.py[cod]
venv/
.venv/

# ===== log =====
*.log
logs/

# ===== intermediate products =====
*.o
*.obj
*.elf
*.hex
*.map
*.lst

# ===== large objects =====
*.zip
*.7z
*.rar
*.iso
*.exe
*.msi
*.dmg

# ===== private messages =====
.env
.env.local
*.local
secrets/
node_modules/
```

