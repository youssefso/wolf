using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Playerhealth : MonoBehaviour {

	public class Stats {
		public int health = 100;
	}
	private Transform bar;
	float x;
	public Stats health = new Stats();
	// Use this for initialization
	void Start ()
	{
		Transform health = transform.Find("HealthBar");
		bar = health.transform.Find("Bar");
	}
	void Update ()
	{
		x = (float)health.health / 100f;
		bar.localScale = new Vector3(x, 1f);
	}
	public void DamagePlayer (int damage) {
		health.health -= damage;
		if (health.health <= 0)
			Destroy(gameObject);
	}
}
