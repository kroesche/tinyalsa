#include <tinyalsa/pcm-config.h>

#include <tinyalsa/pcm-format.h>

#include <stdlib.h>

struct pcm_config {
    /** The number of channels in a frame */
    unsigned int channels;
    /** The number of frames per second */
    unsigned int rate;
    /** The number of frames in a period */
    unsigned int period_size;
    /** The number of periods in a PCM */
    unsigned int period_count;
    /** The sample format of a PCM */
    enum pcm_format format;
    /* Values to use for the ALSA start, stop and silence thresholds.  Setting
     * any one of these values to 0 will cause the default tinyalsa values to be
     * used instead.  Tinyalsa defaults are as follows.
     *
     * start_threshold   : period_count * period_size
     * stop_threshold    : period_count * period_size
     * silence_threshold : 0
     */
    /** The minimum number of frames required to start the PCM */
    unsigned int start_threshold;
    /** The minimum number of frames required to stop the PCM */
    unsigned int stop_threshold;
    /** The minimum number of frames to silence the PCM */
    unsigned int silence_threshold;
};

struct pcm_config *pcm_config_malloc(void)
{
    return malloc(sizeof(struct pcm_config));
}

void pcm_config_free(struct pcm_config *config)
{
    free(config);
}

int pcm_config_get_channels(const struct pcm_config *config, unsigned int *channels)
{
    *channels = config->channels;
    return 0;
}

int pcm_config_get_rate(const struct pcm_config *config, unsigned int *rate)
{
    *rate = config->rate;
    return 0;
}

int pcm_config_get_period_size(const struct pcm_config *config, unsigned int *period_size)
{
    *period_size = config->period_size;
    return 0;
}

int pcm_config_get_period_count(const struct pcm_config *config, unsigned int *period_count)
{
    *period_count = config->period_count;
    return 0;
}

int pcm_config_get_format(const struct pcm_config *config, enum pcm_format *format)
{
    *format = config->format;
    return 0;
}

int pcm_config_get_start_threshold(const struct pcm_config *config, unsigned int *start_threshold)
{
    *start_threshold = config->start_threshold;
    return 0;
}

int pcm_config_get_stop_threshold(const struct pcm_config *config, unsigned int *stop_threshold)
{
    *stop_threshold = config->stop_threshold;
    return 0;
}

int pcm_config_get_silence_threshold(const struct pcm_config *config, unsigned int *silence_threshold)
{
    *silence_threshold = config->silence_threshold;
    return 0;
}

int pcm_config_set_channels(struct pcm_config *config, unsigned int channels)
{
    config->channels = channels;
    return 0;
}

int pcm_config_set_rate(struct pcm_config *config, unsigned int rate)
{
    config->rate = rate;
    return 0;
}

int pcm_config_set_period_size(struct pcm_config *config, unsigned int period_size)
{
    config->period_size = period_size;
    return 0;
}

int pcm_config_set_period_count(struct pcm_config *config, unsigned int period_count)
{
    config->period_count = period_count;
    return 0;
}

int pcm_config_set_format(struct pcm_config *config, enum pcm_format format)
{
    config->format = format;
    return 0;
}

int pcm_config_set_start_threshold(struct pcm_config *config, unsigned int start_threshold)
{
    config->start_threshold = start_threshold;
    return 0;
}

int pcm_config_set_stop_threshold(struct pcm_config *config, unsigned int stop_threshold)
{
    config->stop_threshold = stop_threshold;
    return 0;
}

int pcm_config_set_silence_threshold(struct pcm_config *config, unsigned int silence_threshold)
{
    config->silence_threshold = silence_threshold;
    return 0;
}

