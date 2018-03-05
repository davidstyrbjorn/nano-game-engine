def main():
    import shutil
    
    project_path = ""
    project_name = ""
    project_author = ""

    print("Welcome to the Nano Game Engine project creator!\n")
    
    # Copy the template_folder to target location
    print("(ending with a slash) (forward slashes only)")
    project_path = input("path for your new project>")
    project_name = input("name for your new project>")    
    
    shutil.copytree("../../../empty_project", project_path+project_name)
    
    # Crate nano.txt file with correct info written to it
    project_author = input("name of the project author>")
    
    file = open(project_path + project_name + "/nano.txt", "w")
    file.write("project_name " + project_name + "\n")
    file.write("author " + project_author + "\n")
    file.write("local_path " + project_path + project_name)

    file.close()
    
if __name__ == "__main__":
    main()
