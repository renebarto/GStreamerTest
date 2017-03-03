#include <iostream>

#include <gst/gst.h>

int main (int argc,
      char *argv[])
{
    const gchar *nano_str;

    gst_init(nullptr, nullptr);
    if (!gst_is_initialized())
    {
        std::cout << "GStreamer initialization failed" << std::endl;
        return 1;
    }
    guint major, minor, micro, nano;
    gst_version(&major, &minor, &micro, &nano);
    if (nano == 1)
        nano_str = "(CVS)";
    else if (nano == 2)
        nano_str = "(Prerelease)";
    else
        nano_str = "";
    std::cout << "This program is linked against GStreamer " << major << "." << minor << "." << micro << " " << nano_str << std::endl;

    gboolean silent = FALSE;
    gchar * savefile = nullptr;
    GOptionContext * ctx;
    GError * err = nullptr;
    GOptionEntry entries[] =
    {
        { "silent", 's', 0, G_OPTION_ARG_NONE, &silent, "do not output status information", nullptr },
        { "output", 'o', 0, G_OPTION_ARG_STRING, &savefile, "save xml representation of pipeline to FILE and exit", "FILE" },
        {nullptr }
    };
    ctx = g_option_context_new("- Your application");
    g_option_context_add_main_entries(ctx, entries, nullptr);
    g_option_context_add_group(ctx, gst_init_get_option_group());
    if (!g_option_context_parse(ctx, &argc, &argv, &err))
    {
        g_print("Failed to initialize: %s\n", err->message);
        g_clear_error(&err);
        g_option_context_free(ctx);
        return 1;
    }
    g_option_context_free (ctx);
    std::cout << "Run me with --help to see the Application options appended." << std::endl;

    GstRegistry * registry = gst_registry_get();

    GList *l = gst_registry_get_feature_list(registry, GST_TYPE_ELEMENT_FACTORY);
    GList *i = l;
    GList *e = g_list_last(i);
    for(;;)
    {
        gchar * name;
        g_object_get(G_OBJECT(i->data), "name", &name, NULL);
        printf("%s\n", name);
        g_free(name);
        if (i == e) break;
        i = g_list_next(i);
    }
    g_list_free(l);

    GstElementFactory *factory = gst_element_factory_find("fakesrc");
    /* create element */
    if (!factory)
    {
        g_print("You don’t have the ’fakesrc’ element installed!\n");
        return -1;
    }
    /* display information */
    g_print ("The ’%s’ element is a member of the category %s.\n"
             "Description: %s\n",
             gst_plugin_feature_get_name(GST_PLUGIN_FEATURE(factory)),
             gst_element_factory_get_metadata(factory, GST_ELEMENT_METADATA_KLASS),
             gst_element_factory_get_metadata(factory, GST_ELEMENT_METADATA_DESCRIPTION));

    gchar * name;
    GstElement * element = gst_element_factory_create(factory, "source");
    if (!element) {
        g_print("Failed to create element of type ’fakesrc’\n");
        return -1;
    }
    name = gst_object_get_name(GST_OBJECT(element));
    g_print("The name of the element is ’%s’.\n", name);
    g_free(name);
    g_object_get(G_OBJECT(element), "name", &name, NULL);
    g_print("The name of the element is ’%s’.\n", name);
    g_free(name);

    gst_object_unref(GST_OBJECT(element));
    gst_object_unref(GST_OBJECT(factory));

    /* create pipeline */
    GstElement * pipeline = gst_pipeline_new ("my-pipeline");
    /* create elements */
    GstElement * source = gst_element_factory_make("fakesrc", "source");
    GstElement * filter = gst_element_factory_make("identity", "filter");
    GstElement * sink = gst_element_factory_make("fakesink", "sink");

    /* must add elements to pipeline before linking them */
    gst_bin_add_many(GST_BIN(pipeline), source, filter, sink, NULL);
    /* link */
    if (!gst_element_link(source, filter))
    {
        g_warning("Failed to link elements!");
    }
    if (!gst_element_link(filter, sink))
    {
        g_warning("Failed to link elements!");
    }
    if (!gst_element_link_many (source, filter, sink, NULL))
    {
        g_warning("Failed to link elements!");
    }

    gst_object_unref(GST_OBJECT(pipeline));
//    gst_object_unref(GST_OBJECT(source));
//    gst_object_unref(GST_OBJECT(filter));
//    gst_object_unref(GST_OBJECT(sink));

    gst_deinit();
    return 0;
}
