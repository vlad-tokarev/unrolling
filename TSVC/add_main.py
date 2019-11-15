def add_new_main(path_original, path_destination):
    with open(path_original) as f:
        content = f.readlines()
    content = [x.strip() for x in content]

    with open(path_destination) as t:
        main_file = t.readlines()
    main_file = [x.strip() for x in main_file]

    new_content = []
    for line in content:
        if not (not ('int main(int argc, char **argv)' in line) or 'extern' in line):
            break
        else:
            new_content.append(line)
    new_file = new_content + main_file

    with open(path_original, 'w+') as f:
        for item in new_file:
            f.write("%s\n" % item)
