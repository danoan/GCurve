#include "gcurve/test/control/GCAttributeWriter.h"

using namespace GCurve::Test;

GCAttributeWriter::GCAttributeWriter(bool activeFlag):activeFlag(activeFlag),
                                                      initialized(false),
                                                      completed(false)
{
    ofs.precision(20);
};

void GCAttributeWriter::init(std::string filepath)
{
    if(!activeFlag) return;

    if(initialized && !completed) throw std::runtime_error("Initialization without finishing previous task.");

    lines = 0;
    finalFilepath = filepath;
    tempFilepath = filepath + ".temp";

    ofs.open(tempFilepath);
    initialized = true;
    completed = false;
}


void GCAttributeWriter::close()
{
    if(!activeFlag) return;
    ofs.close();

    ofs.open(finalFilepath);
    ofs << lines+1 << std::endl;


    std::ifstream tempfs(tempFilepath);
    ofs << tempfs.rdbuf();

    tempfs.close();
    ofs.close();

    remove(tempFilepath.c_str());

    completed = true;
    initialized = false;
}