import h5py
import json



def readNDE(nde_file):
    """
    Reads the NDE file and returns its data and information. 

    Parameters
    ----------
    nde_file : STR
        Full path to the NDE file.

    Returns
    -------
    data : DICT
        Dict containing the A-Scans amplitude for each group.
    domain_setup : DICT
        Dict containing all the information of the domain setup.
    """    
    f = h5py.File(nde_file, 'r')

    # Gets and decodes the json file about the configuration 
    json_str = f['Domain/Setup'][()]
    domain_setup = json.loads(json_str)


    NGroups = len( domain_setup["groups"] )
    group_list = list(range(NGroups))
    data = {}


    # Loops over each group contained in the file 
    for gr in group_list:
        data[gr] = {}
        
        if 'dataset' in domain_setup["groups"][gr-1].keys():
            data_str = 'dataset'
            
            if 'ascan' in domain_setup["groups"][gr-1][data_str]:
                # Reads their A-Scans using the path given in the domain setup
                path = domain_setup["groups"][gr-1][data_str]['ascan']['amplitude']['path']                
                data[gr]['data_array'] = f[ path ][:]

    f.close()
    return data,domain_setup
