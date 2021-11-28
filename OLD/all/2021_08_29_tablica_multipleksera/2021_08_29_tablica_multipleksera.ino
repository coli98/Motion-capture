void setup()
{
  Serial.begin(57600);
  while (!Serial);

  char vec[] = { 2, 5, 3, 0, 0, 1 };
  print(vec, sizeof(vec));

  compact(vec, sizeof(vec));
  print(vec, sizeof(vec));

  vec[1] = 0;
  print(vec, sizeof(vec));

  compact(vec, sizeof(vec));
  print(vec, sizeof(vec));
}

void loop()
{
}

void compact(char* vec, size_t len)
{
  int i = 0;
  for (; i < len && vec[i] != 0; i++);
  if (i == len) return;
  int j = i;
  for (; i < len; i++) {
    char c = vec[i];
    if (c != 0) {
      vec[j++] = c;
      vec[i] = 0;
    }
  }
}

void print(char* vec, size_t len)
{
  for (int i = 0; i < len; i++) {
    unsigned c = vec[i];
    if (c < 16) Serial.print(0);
    Serial.print(c, HEX);
    if (i + 1 < len) Serial.print('-');
  }
  Serial.println();
}
