#include <gstreamer++/pipeline.h>

//#include <cassert>
//#include <iostream>
//#include <sstream>
#include <gst/gst.h>

using namespace GStreamer;

Pipeline::Pipeline(GstPipeline * pipelineInternal)
    : Bin(GST_BIN(pipelineInternal))
    , _pipelineInternal(pipelineInternal)
    , _thread()
    , _bus(std::make_shared<Bus>(gst_pipeline_get_bus(pipelineInternal)))
{
}

Pipeline::~Pipeline()
{
    ChangeState(State::Null);
}