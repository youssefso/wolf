using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemyhealth : MonoBehaviour {

	private Transform bar;
	public class EnemyHealth {
		public int Health = 100;
	}
	private float x;
	public EnemyHealth enemyhealth = new EnemyHealth();
	void Start ()
	{
		Transform health = transform.Find("HealthBar");
		bar = health.transform.Find("Bar");
		if (bar == null)
		Debug.Log("Barrr");
	}
	void Update ()
	{
		x = (float)enemyhealth.Health / 100f;
		bar.localScale = new Vector3(x, 1f);
	}
	public void DamageEnemy (int damage) {
		enemyhealth.Health -= damage;
		if (enemyhealth.Health <= 0)
			Destroy(gameObject);
	}
}
