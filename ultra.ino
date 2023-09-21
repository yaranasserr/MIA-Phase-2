
long get_distance() {
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure distance
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

void avoidCollision(int desiredDistance) {
  long distance = get_distance();
  // Check if the measured distance is less than desired distance
  if (distance < desiredDistance) {
    // Take action to avoid collision, stop or reverse the direction of motion
    Stop();
  }
}

