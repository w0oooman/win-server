attrib -r -h -s BuildTime.* /s
attrib -r -h -s *.intermediate.manifest /s
attrib -r -h -s *.lib /s
attrib -r -h -s *.dll /s
attrib -r -h -s *.exe /s
attrib -r -h -s *.dep /s
attrib -r -h -s *.user /s
attrib -r -h -s *.obj /s
attrib -r -h -s *.idb /s
attrib -r -h -s *.aps /s
attrib -r -h -s *.res /s
attrib -r -h -s *.plg /s
attrib -r -h -s *.opt /s
attrib -r -h -s *.ncb /s
attrib -r -h -s *.bak /s
attrib -r -h -s *.tmp /s
attrib -r -h -s *.idb /s
attrib -r -h -s *.exp /s
attrib -r -h -s *.ilk /s
attrib -r -h -s *.pdb /s
attrib -r -h -s *.tli /s
attrib -r -h -s *.tlh /s
attrib -r -h -s disasm.asm /s
attrib -r -h -s *.trg /s
attrib -r -h -s *.pch /s
attrib -r -h -s *.~* /s
attrib -r -h -s *.ddp /s
attrib -r -h -s *.suo /s
attrib -r -h -s *.scc /s
attrib -r -h -s thumbs.db /s
attrib -r -h -s *.xml /s
attrib -r -h -s *.cod /s
attrib -r -h -s *.ipch /s
attrib -r -h -s *.sdf /s
attrib -r -h -s *.i /s

del /s BuildLog.htm *.intermediate.manifest *.dep *.obj *.idb *.aps *.res *.plg *.opt *.ncb *.bak *.tmp *.idb *.exp *.ilk *.pdb *.tli *.tlh disasm.asm *.trg *.pch *.~* *.ddp *.scc thumbs.db *.cod *.ipch *.sdf *.ldb

echo "没清理*.user 和 隐藏的*.suo 文件!!"
rem del /s *.user *.suo 


rem del /s *.i

