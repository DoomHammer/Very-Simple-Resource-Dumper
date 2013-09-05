#ifndef CMDLINE_H
#define CMDLINE_H

enum Operation {
    DumpHeader    = 0,
    DumpResources = 1
};

class CmdLine
{
public:
    CmdLine(int argc, const char **argv);

    const char *input()  const
    {
        return m_inputFile;
    }

    const char *output() const
    {
        return m_outputFile;
    }

    Operation operation() const
    {
        return m_operation;
    }

protected:
    const char *m_inputFile;
    const char *m_outputFile;
    Operation  m_operation;
};
#endif
