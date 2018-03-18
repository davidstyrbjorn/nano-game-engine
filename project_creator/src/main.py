def main():
    import shutil
    
    project_path = ""
    project_name = ""
    project_author = ""
    startup_level = ""

    print("Welcome to the Nano Game Engine project creator!\n")
    
    # Copy the template_folder to target location
    print("(ending with a slash) (forward slashes only)")
    project_path = input("path for your new project>")
    project_name = input("name for your new project>")    

    #copy the empty_project folder (not including the 2 .exe files we need)
    shutil.copytree("../../../empty_project", project_path+project_name)
    #copy the two .exe files taken from build_central
    shutil.copyfile("../../../../NanoGameEngineSolution/build_central/editor/editor.exe", project_path+project_name+"/editor.exe")
    
    # Crate nano.txt file with correct info written to it
    project_author = input("name of the project author>")
    startup_level = input("startup level name>")
    
    file = open(project_path + project_name + "/nano.txt", "w")
    file.write("project_name " + project_name + "\n")
    file.write("author " + project_author + "\n")
    file.write("local_path " + project_path + project_name + "\n")
    file.write("startup_level " + startup_level + "\n")

    #create the startup level
    shutil.copyfile("../../../empty_level.txt", project_path+project_name+"/resources/levels/"+startup_level + ".txt")

    file.close()
    
if __name__ == "__main__":
    main()
