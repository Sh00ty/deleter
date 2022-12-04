#!/usr/bin/env python
# -*- coding: utf-8 -*-


import sys
import subprocess


def findd(folder, name):
    if name[-1] == '\\':
        name = name[:-1]
        name = name + '*'
    if name[0] == '\\':
        name = name[1:]
        name = '*' + name
    comm = ['find', folder, '-name', name]

    proc = subprocess.Popen(comm, stdout=subprocess.PIPE,stderr = subprocess.PIPE)

    find_list = proc.stdout.read()
    find_list = find_list.decode('utf-8')
    find_list = str(find_list)
    find_list = find_list[0:-1]

    err = proc.stderr.read()
    if err != b'':
        err = str(err)
        err = err[2:-3]
        lis = err.split(':')

        if lis[2] == ' No such file or directory':
            print('\n[ERROR] THERE_IS_ERROR:-::No such file or directory::')
            return err, -1
        elif lis[2] == ' Permission denied':
            print('\n[COMMENT]:',err,)

    return find_list, 0


def file_of(dir):
    comm = ['file', dir]
    proc = subprocess.Popen(comm, stdout = subprocess.PIPE)
    out = str(proc.stdout.read())
    out = out[2:-3]
    out = out.split(':')
    return out[-1]


def ls_of(dir):
    comm = ['ls', dir]
    proc = subprocess.Popen(comm, stdout = subprocess.PIPE)
    out = str(proc.stdout.read())
    out = out[2:-3]
    return out


def size_of(dir):
    comm =['du','-h', dir]
    if file_of(dir) == ' directory':
        return None
    proc = subprocess.Popen(comm,stdout = subprocess.PIPE,stderr = subprocess.PIPE)
    err = proc.stderr.read()
    if err != b'':
        err = str(err)
        err = err[2:-3]
        lis = err.split(':')
        if lis[2] == ' No such file or directory':
            return '[-------------------------------------]'
    out = str(proc.stdout.read())[2:-3]
    out = out.split('\\t')
    return out[0]


def cat_of(dir):
    comm = ['cat', dir]
    proc = subprocess.Popen(comm, stdout = subprocess.PIPE)
    return str(proc.stdout.read())[2:-3]


def diff_of(file1, file2):
    if type(file1) != str or type(file2) != str:
        return -1
    comm = ['diff', file1, file2]
    proc = subprocess.Popen(comm, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    out = proc.stdout.read()
    err = proc.stderr.read()

    if err == b'':
        if out == b'':
            return None
        else:
            out= str(out)
            out = out[2:-3]
            return 0
    else:
        err = str(err)
        err = err[2:-3]
        print('####### SOME ERROR #######',err)
        return -1


def rm(dir):
    comm = ['rm', '-r', dir]
    print('DO YOU WANT TO DELETE %s?' %(dir))
    res = input('Yes/n::')
    if res == 'y' or res == 'Y' or res == 'yes' or res == 'Yes':
        subprocess.call(comm)
        print('%s removed' %(dir))
    else:
        print('Ok, %s won\'t be deleted' %(dir))


def rm_y(dir):
    comm = ['rm', '-r', dir]
    res = input()
    subprocess.call(comm)
    print('%s removed' %(dir))


######################################
######################################
######################################
######################################


def finder(folder,name):
    del_num = 'qwer'
    name_for_restart = name
    while del_num != None or del_num != 'exit' or del_num != '':
        if folder == '' or name == '':
            print('#########################################################################\nCLOSED')
            return None
        if folder == 'Desktop':
            folder = '/Users/pavelshykov/Desktop'
        if folder == 'Downloads':
            folder = '/Users/pavelshykov/Downloads'
        if folder == 'home' or folder == 'user' or folder == '~':
            folder = '/Users/pavelshykov'

        a, err_flag  = findd(folder, name)
        if name[0] == '\\':
            name = name[1:]
        if name[-1] == '\\':
            name = name[0:-1]
        if err_flag == 0:
            if name in a:
                lis = a.split('\n')
                for i in range(1,len(lis) + 1):#добавил + 1
                    fil = ''
                    for g in range(len(lis[i-1]) - 1,0,-1):
                        if (lis[i-1])[g] == '/':
                            fil = lis[i-1]
                            fil = fil[g +1:]
                            break
                    print(i, lis[i-1], fil, file_of(lis[i-1]), size_of(lis[i-1]))

                if i > 0:
                    print('#################  Found %s of \'%s\' names' %(i, name))

                    del_num = input('CHOOSE NOUMBERS TO DELETE (or put: show + noumber)::')
                    if del_num == '' or del_num == 'None' or del_num == 'exit':
                        print('######################################################## Closed')
                        return None
                        sys.exit()
                        print('ahahahahhahahahahahahahahahah')
                    del_num = del_num.split()
                    while del_num[0] == 'show' or del_num[0] == 'Show':
                        for it in range(1,len(del_num)):
                            print(del_num[0], del_num[it])
                            print('##############################')
                            try:
                                dash_list = []
                                if '-' in del_num[it]:
                                    dash_list = del_num[it].split('-')
                                else:
                                    dash_list = [int(del_num[it]),int(del_num[it])]
                                for if_dash in range(int(dash_list[0]),int(dash_list[1]) + 1):
                                    g = if_dash
                                    if file_of(lis[g - 1]) == ' directory':
                                        ls = ls_of(lis[g - 1])
                                        ls = ls.split('\\n')
                                        for h in ls:
                                            print(h)
                                    elif file_of(lis[g - 1]) == ' empty':
                                        print('file is empty')
                                    elif file_of(lis[g - 1]) == ' ASCII text':
                                        cat = cat_of(lis[g - 1])
                                        cat = cat.split('\\n')
                                        for h in cat:
                                            print(h)
                                    elif ' TIM' in file_of(lis[g - 1]) or ' PDF' in file_of(lis[g - 1]) or ' PNG' in file_of(lis[g - 1]) or ' JPEG' in file_of(lis[g-1]) or ' HEIF' in file_of(lis[g-1]):
                                        subprocess.call(['open', lis[g-1]])
                                    else:
                                        subprocess.call(['open', lis[g-1]])
                            except:
                                print('Your input after show must be integer less then %s' %(i))
                                print('##############################')
                        del_num = input('CHOOSE NOUMBERS TO DELETE (or put: show + noumber)::')
                        if del_num == '' or del_num == 'None' or del_num == 'exit':
                            print('#################################################### Closed')
                            sys.exit()
                        del_num = del_num.split()

                    for i in del_num:
                        try:
                            if '-' in i:
                                i_list = i.split('-')
                                start = int(i_list[0])
                                stop = int(i_list[1]) + 1
                            else:
                                start = int(i)
                                stop = start + 1
                            for what_del in range(start,stop):
                                rm(lis[what_del-1])
                        except:
                            print(i,'isn\'t noumber or noumber is more then files found')

                elif i == 0:
                    print('#################  Found %s of \'%s\' names, IT\'S OK' %(i, name))
            else:
                print('Didn\'t find \'%s\' in %s' %(name,folder))
                return None
                sys.exit()
        elif err_flag == -1:#Oшибка:No such file or directory
            print('::PUT FULL DIRECTION or PUT CORRECT DIRECTORY::\nTo exit push Enter')
            acti = input('name::')
            v = input('CORRECT_folder::')
            finder(v,acti)

        acti= name_for_restart
        v = folder
        finder(v,acti)


#####################################
#####################################
#####################################
#####################################


def find_duplicated(dir, expansion):
    lis ,err_flag = findd(dir, expansion)

    inp = 'inp'
    lis_up = []
    sizes = []
    dic = {}
    equal_list = []
    sum_for_mas = 0

    lis = lis.split('\n')
    for i in range(len(lis)):
        sizes.append(size_of(lis[i]))
        if dic.get(sizes[i]) == None:
            dic[sizes[i]] = [lis[i]]
        else:
            pasted = dic[sizes[i]]
            pasted.append(lis[i])
            dic[sizes[i]] = pasted

    for i in dic.keys():
        if len(dic[i]) > 1:
            for g in range(len(dic[i])):
                if dic[i][g] != -1:
                    s = 0
                    for t in range(g + 1, len(dic[i])):
                        if (dic[i][t] == -1):
                            continue
                        if (diff_of(dic[i][g], dic[i][t]) == None):
                            if s == 0:
                                equal_list.append([])
                                equal_list[sum_for_mas].append(dic[i][g])
                                equal_list[sum_for_mas].append(dic[i][t])
                                s += 1
                            elif s != 0:
                                equal_list[sum_for_mas].append(dic[i][t])
                            dic[i][t] = -1

                    if s != 0:
                        sum_for_mas += 1


    for i in range(1, len(equal_list) + 1):
        print(i)
        for g in range(len(equal_list[i-1])):
            print(equal_list[i-1][g])
        print('\n')


    inp = input('If you want to remove them enter :: number of string and number of file in string\nIf you want to open them enter :: show + number of string(you can print one if you enter show "num" one)\n::')
    while inp != None or inp != '':

        if inp != '':
             inp = inp.split()
        if inp == '' or inp == None:
            print('######################################################## Closed')
            return None
            break
        elif inp[0] == 'show' or inp[0] == 'SHOW' or inp[0] == 'Show':

            if inp[-1] == 'one':
                for p in range(1,len(inp) - 1):
                    if '-' in inp[p]:
                        bash = inp[p].split('-')
                        start = int(bash[0])
                        stop = int(bash[1])
                    else:
                        start = int(inp[p])
                        stop = int(inp[p])
                    for i in range(start, stop + 1):
                            subprocess.call(['open', equal_list[i-1][0]])

            else:
                for p in range(1,len(inp)):
                    if '-' in inp[p]:
                        bash = inp[p].split('-')
                        start = int(bash[0])
                        stop = int(bash[1])
                    else:
                        start = int(inp[p])
                        stop = int(inp[p])
                    for i in range(start, stop + 1):
                        for g in range(len(equal_list[i-1])):
                            subprocess.call(['open', equal_list[i-1][g]])

        elif inp[0] == 'rm' or inp[0] == 'RM' or inp[0] == 'Rm':
            if inp[1] =='-y':
                for p in range(2,len(inp)):
                    if '-' in inp[p]:
                        bash = inp[p].split('-')
                        start = int(bash[0])
                        stop = int(bash[1])
                    else:
                        start = int(inp[p])
                        stop = int(inp[p])
                    for i in range(start, stop + 1):
                        for g in range(len(equal_list[i-1])):
                            rm_y(equal_list[i-1][g])
            else:
                for p in range(1,len(inp)):
                    if '-' in inp[p]:
                        bash = inp[p].split('-')
                        start = int(bash[0])
                        stop = int(bash[1])
                    else:
                        start = int(inp[p])
                        stop = int(inp[p])
                    for i in range(start, stop + 1):
                        for g in range(len(equal_list[i-1])):
                            rm(equal_list[i-1][g])

        inp = input('If you want to remove them enter :: rm + number of string\nIf you want to open them enter :: show + number of string(you can print one if you enter show "num" one)\n::')


############################## 
##############################
##############################


def find_duplicated_files():
    folder = input('ENTER DIRECTORY::')
    if folder == '':
        print('#########################################################################\nCLOSED')
        return None
    if folder == 'Desktop':
        folder = '/Users/pavelshykov/Desktop'
    if folder == 'Downloads':
        folder = '/Users/pavelshykov/Downloads'
    if folder == 'home' or folder == 'user' or folder == '~':
        folder = '/Users/pavelshykov'

    expansion = input('ENTER expansions or ENTER ALL::')
    excepts = []
    expansion = expansion.split()

    if 'except' in expansion:
        u = len(expansion) - 1
        while expansion[u] != 'except':
            excepts.append(expansion[u])
            u -= 1
    if expansion[0] == 'ALL' or expansion[0] == 'all':
        expansion = 'pdf HEIC txt JPG jpg png doc xls app py rar mp3 wav c h'
        expansion = expansion.split()

    for i in expansion:
        if i =='pdf' and 'pdf' not in excepts:
            find_duplicated(folder, '\\pdf')
        if i == 'HEIC' and 'HEIC' not in excepts:
            find_duplicated(folder, '\\HEIC')
        if i =='txt' and 'txt' not in excepts:
            find_duplicated(folder, '\\txt')
        if i =='JPG' and 'JPG' not in excepts:
            find_duplicated(folder, '\\JPG')
        if i =='jpg' and 'jpg' not in excepts:
            find_duplicated(folder, '\\jpg')
        if i =='png' and 'png' not in excepts:
            find_duplicated(folder, '\\png')
        if i =='doc' and 'doc' not in excepts:
            find_duplicated(folder, '\\doc')
        if i =='xls' and 'xls' not in excepts:
            find_duplicated(folder, '\\xls')
        if i =='app' and 'app' not in excepts:
            find_duplicated(folder, '\\.app')
        if i =='py' and 'py' not in excepts:
            find_duplicated(folder, '\\.py')
        if i =='rar' and 'rar' not in excepts:
            find_duplicated(folder, '\\rar')
        if i =='mp3' and 'mp3' not in excepts:
            find_duplicated(folder, '\\mp3')
        if i =='wav' and 'wav' not in excepts:
            find_duplicated(folder, '\\wav')
        if i == 'heic' and 'heic' not in excepts:
            find_duplicated(folder, '\\heic')
        if i == 'c' and 'c' not in excepts:
            find_duplicated(folder, '\\c') 
        if i == 'h' and 'h' not in excepts:
            find_duplicated(folder, '\\h')

##############################    
##############################         MAIN
##############################         MAIN
##############################         MAIN
main_choose = 'a'
while main_choose != 'exit' and main_choose != '':
    main_choose = input('HELLO USER\nYOU ALWAYS CAN ENTER \'\' TO EXIT\nTO FIND DUPLICATED FILES PRESS 1\nTO FIND FILES BY NAME PRESS 2\n::')
    if main_choose =='help':
        print('THIS IS HELP:::\nThis programm can find equal files and find files by names(parts of names)')
    if '1' in main_choose:
        find_duplicated_files()
        print('###################################### #### ## #')
    if '2' in main_choose:
        print('To exit push Enter')
        acti = input('name::')
        v = input('folder::')
        finder(v,acti)
        print('###################################### #### ## #')
##############################          MAIN
##############################          MAIN
##############################          MAIN
##############################          MAIN
