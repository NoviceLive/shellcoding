char *
esc_str_to_bytes(const char *str, char *bytes);
char *
esc_str_to_bytes(const char *chexstr, char *bytes)
{
  size_t i;
  char buf[3];
  int n = 0;
  for (i = 0; i < strlen(chexstr); ++i) {
    if (chexstr[i] == '\\') {
      strncpy(buf, chexstr + i + 2, 2);
      buf[2] = '\0';
      bytes[n] = (char)strtol(buf, NULL, 16);
      ++n;
    }
  }
  bytes[n] = '\0';
  return bytes;
}
